import csv

name = input("Name: ")
number = input("Number: ")
with open("phonebook.csv", "a") as file:
    writer = csv.DictWriter(file, fieldnames = ["Name","Number"])
    writer.writerow({"Name":name, "Number": number})
