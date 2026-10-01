import csv

filename = "requirements.tsv"

with open(filename, newline="", encoding="utf-8-sig") as file:
    reader = csv.DictReader(file, delimiter="\t")

    complete = []
    missing_test = []

    for row in reader:
        if row["Test-ID"].strip():
            complete.append(row["Krav-ID"])
        else:
            missing_test.append(row["Krav-ID"])

print("=== Automatic Gap Check ===")
print(f"Complete requirements: {len(complete)}")
print(f"Missing tests: {len(missing_test)}")

if complete:
    print("\nComplete:")
    for req in complete:
        print(f"  {req}")

if missing_test:
    print("\nMissing test:")
    for req in missing_test:
        print(f"  {req}")
else:
    print("\nAll requirements have a test.")
