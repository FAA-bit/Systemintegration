# Day 6 Notes - WSL, Network Namespaces, Routing and nftables

This document records what I learned and the commands I used during the Day 6 networking lab. The lab creates a small, isolated network inside Linux or WSL2. It contains an IoT network, a services network, an administration network and a router between them.

## 1. What is WSL?

WSL stands for **Windows Subsystem for Linux**. It allows Linux tools and commands to run on a Windows computer without installing a separate Linux computer. For this lab, WSL provides the Ubuntu or Debian environment where Linux network namespaces, `ip`, `nft` and Python can run.

The lab must be run from the Linux terminal. PowerShell commands and Linux commands are not interchangeable. The Windows project directory is normally available from WSL below `/mnt/c/`.

## 2. Check the WSL installation

Open PowerShell and run:

```powershell
wsl --status
wsl --list --verbose
```

These commands show whether WSL is installed, which Linux distributions are available and whether a distribution uses WSL 1 or WSL 2.

If the WSL service is available but not running, open PowerShell as Administrator and check it with:

```powershell
Get-Service WslService
```

If the service exists, it can be configured to start manually and then started with:

```powershell
Set-Service WslService -StartupType Manual
Start-Service WslService
```

The service name can differ between Windows versions. If `Get-Service WslService` reports that it cannot find the service, use `wsl --status` and `wsl --list --verbose` to inspect the installed WSL configuration instead of assuming that the service is missing from the whole system.

## 3. Install or open Ubuntu

If no Linux distribution is installed, open PowerShell as Administrator and run:

```powershell
wsl --install -d Ubuntu
```

After the installation, verify the distribution:

```powershell
wsl --list --verbose
```

Start Ubuntu from the Start menu or with:

```powershell
wsl -d Ubuntu
```

The first start asks for a Linux username and password. The password is used for `sudo`; it is not displayed while typing.

## 4. Install the Linux tools

In the WSL or Ubuntu terminal, install the tools required by the lab:

```bash
sudo apt-get update
sudo apt-get install iproute2 nftables python3 -y
```

The tools have these roles:

| Tool | Role in the lab |
| --- | --- |
| `ip` | Creates namespaces, virtual Ethernet links, addresses and routes |
| `nft` | Loads and inspects firewall rules |
| `python3` | Runs the TCP probe service and connectivity tests |
| `sysctl` | Enables IPv4 forwarding in the router namespace |

Check that the main tools are available:

```bash
nft --version
which nft
ip -V
python3 --version
```

`nftables` is the Linux firewall framework. The `nft` command is the program used to validate, load and inspect nftables rules.

## 5. Open the project directory

Move to the day 6 directory in the Linux terminal. The exact path depends on where the Windows project is stored. For example:

```bash
cd "/mnt/d/STI - IoT25-VC/Systemintegration/Systemintegration/src/day_6"
```

Use quotes when a path contains spaces. Confirm that the expected files are present:

```bash
pwd
ls -la
```

You should see files such as `lab.sh`, `rules.nft`, `check.py`, `probe_service.py` and `README.md`.

## 6. How the lab network is built

The script `lab.sh up` creates four named Linux network namespaces:

| Namespace | Purpose | Address or interfaces |
| --- | --- | --- |
| `iot25-d6-iot` | Simulated IoT device network | `10.60.10.10/24` |
| `iot25-d6-srv` | Network containing the test services | `10.60.20.10/24` |
| `iot25-d6-admin` | Simulated administration network | `10.60.30.10/24` |
| `iot25-d6-router` | Routes and filters traffic | `10.60.10.1`, `10.60.20.1`, `10.60.30.1` |

Each client namespace is connected to the router by one end of a virtual Ethernet pair. The client side is named `eth0`; the router side is named `r-iot`, `r-srv` or `r-admin`.

The default gateways are:

```text
IoT:            10.60.10.1
Services:       10.60.20.1
Administration: 10.60.30.1
```

The virtual links are created inside the namespaces, so the lab does not connect these networks to the normal Windows or host LAN.

## 7. Start and test the lab

Run these commands from the day 6 directory in WSL:

```bash
sudo bash lab.sh up
sudo bash lab.sh status
sudo bash lab.sh test
```

What each command does:

- `up` creates the namespaces and virtual links, assigns IP addresses, enables forwarding, loads the firewall and starts the TCP test service.
- `status` prints the namespaces, the router routes and the active nftables rules.
- `test` runs fresh TCP connections from the IoT, services and administration namespaces.

The server namespace runs a simple Python TCP service. It listens on ports 1883 and 8080 and returns the text `IOT25 TCP probe OK`. These are test ports only; the services are not a real MQTT broker or HTTP server.

The expected result is six passing checks:

```text
PASS srv -> 1883 ALLOW expected ALLOW
PASS srv -> 8080 ALLOW expected ALLOW
PASS iot -> 1883 ALLOW expected ALLOW
PASS iot -> 8080 BLOCK expected BLOCK
PASS admin -> 8080 ALLOW expected ALLOW
PASS admin -> 1883 BLOCK expected BLOCK
```

The first two checks originate in the services namespace. They verify that the test service is running before a firewall result is interpreted. The remaining checks verify the intended policy:

- IoT may reach service port 1883.
- IoT may not reach service port 8080.
- Administration may reach service port 8080.
- Administration may not reach service port 1883.

Each probe creates a new TCP connection and waits up to one second. A blocked connection is expected to fail or to time out. The test is successful when the observed result matches the expected result.

## 8. Inspect addresses, routes and forwarding

Useful inspection commands are:

```bash
sudo ip -n iot25-d6-iot addr
sudo ip -n iot25-d6-iot route
sudo ip -n iot25-d6-router addr
sudo ip -n iot25-d6-router route
sudo ip netns exec iot25-d6-router sysctl net.ipv4.ip_forward
```

Routing and firewall filtering are different concepts:

- **Routing** decides where a packet should go.
- **Forwarding** allows the router kernel to pass a packet between interfaces.
- **Firewall filtering** decides whether that packet is allowed to pass.

The lab enables IPv4 forwarding only inside `iot25-d6-router`. This is enough for packets to travel between the isolated client networks. A route alone is not sufficient if forwarding is disabled or the firewall drops the packet.

## 9. Inspect nftables rules

Display the active firewall rules with:

```bash
sudo ip netns exec iot25-d6-router nft list ruleset
```

The main policy is applied to the `forward` chain because the tested packets travel through the router to another namespace. The rules use a default `drop` policy and explicitly allow the required traffic.

The rules consider values such as:

- source IP address
- destination IP address
- destination port
- connection state

The rule `ct state established,related` allows reply packets belonging to an already permitted connection. Without a rule for established traffic, a request might be allowed while its response is blocked.

The lab does not allow ICMP between all segments. Therefore, a failed `ping` does not automatically prove that an allowed TCP port is broken. Test the actual TCP port with the provided test command.

## 10. Create a firewall backup

After the normal test passes, create a backup of the router's nftables rules:

```bash
sudo bash lab.sh backup
ls -la .state
```

The backup is stored as:

```text
.state/backup.nft
```

The backup contains the firewall rules, but it does not contain every part of the network setup. The namespaces, IP addresses and routes are recreated by `lab.sh up`. A complete production backup would need to include the full network topology as well as the firewall configuration.

## 11. Simulate a broken firewall and restore it

The lab includes a controlled failure exercise:

```bash
sudo bash lab.sh break
sudo bash lab.sh test-broken
sudo bash lab.sh restore
sudo bash lab.sh test
```

`break` replaces the normal rules with a minimal forward chain whose policy is `drop`. `test-broken` expects the cross-network traffic to be blocked. The service checks from the services namespace should still work because they test services locally rather than routing through the firewall.

`restore` loads `.state/backup.nft` again. The final `test` should return to the six normal passing checks. This exercise shows why a configuration change should be tested and why a known-good backup is useful.

## 12. Stop the lab

When finished, remove the lab namespaces and stop the test processes:

```bash
sudo bash lab.sh down
```

The script removes only the named namespaces owned by this lab. The backup and log files remain in `.state`.

Keep the WSL terminal open while the lab is running. If WSL is closed, the processes and virtual network may disappear. If the next start reports an existing owner marker or namespace, inspect the state and run `down` before trying `up` again.

## 13. What I learned

During Day 6, I learned:

- How WSL provides a Linux environment on Windows.
- How network namespaces isolate network stacks and processes.
- How virtual Ethernet pairs connect namespaces to a router.
- How subnets, IP addresses and default gateways work together.
- Why routing, forwarding and firewall filtering are separate steps.
- Why forwarded packets are evaluated in the router's `forward` chain.
- How nftables can allow traffic based on source, destination and port.
- Why established and related connection states are needed for reply traffic.
- Why both allowed and blocked traffic must be tested.
- Why a failed `ping` is not enough to diagnose a TCP networking problem.
- How to create a firewall backup, introduce a controlled failure and restore the working configuration.

The main lesson was that a running service is only one part of communication. Successful communication also requires correct interfaces, addresses, routes, forwarding and firewall rules.

## 14. Final cleanup

Before closing the WSL terminal, run:

```bash
sudo bash lab.sh down
```

This leaves the project files and the firewall backup available for later review while removing the temporary network environment.
