def add_element(set_data, element):
    set_data.add(element)

def remove_element(set_data, element):
    set_data.discard(element)

def contains_element(set_data, element):
    return element in set_data

def get_size(set_data):
    return len(set_data)

def iterate_set(set_data):
    for elem in set_data:
        print(elem, end=" ")
    print()

def intersection(set1, set2):
    return set1.intersection(set2)

def union(set1, set2):
    return set1.union(set2)

def difference(set1, set2):
    return set1.difference(set2)

def is_subset(set1, set2):
    return set1.issubset(set2)

def print_menu():
    print("\nSet Operations Menu:")
    print("1. Add (element)")
    print("2. Remove (element)")
    print("3. Contains (element)")
    print("4. Size")
    print("5. Iterator (print all elements)")
    print("6. Intersection of two sets")
    print("7. Union of two sets")
    print("8. Difference between two sets")
    print("9. Subset check")
    print("10. Exit")

def main():
    set1 = set()
    set2 = set()

    while True:
        print_menu()
        choice = int(input("Enter your choice: "))

        if choice == 1:
            element = int(input("Enter element to add: "))
            add_element(set1, element)
        elif choice == 2:
            element = int(input("Enter element to remove: "))
            remove_element(set1, element)
        elif choice == 3:
            element = int(input("Enter element to check: "))
            if contains_element(set1, element):
                print("Element is in the set.")
            else:
                print("Element is not in the set.")
        elif choice == 4:
            print(f"Size of set: {get_size(set1)}")
        elif choice == 5:
            print("Iterating through set:")
            iterate_set(set1)
        elif choice == 6:
            print("Enter elements for the second set:")
            num_elements = int(input("How many elements in the second set? "))
            for _ in range(num_elements):
                element = int(input("Enter element: "))
                add_element(set2, element)
            result = intersection(set1, set2)
            print(f"Intersection: {result}")
        elif choice == 7:
            print("Enter elements for the second set:")
            num_elements = int(input("How many elements in the second set? "))
            for _ in range(num_elements):
                element = int(input("Enter element: "))
                add_element(set2, element)
            result = union(set1, set2)
            print(f"Union: {result}")
        elif choice == 8:
            print("Enter elements for the second set:")
            num_elements = int(input("How many elements in the second set? "))
            for _ in range(num_elements):
                element = int(input("Enter element: "))
                add_element(set2, element)
            result = difference(set1, set2)
            print(f"Difference: {result}")
        elif choice == 9:
            print("Enter elements for the second set:")
            num_elements = int(input("How many elements in the second set? "))
            for _ in range(num_elements):
                element = int(input("Enter element: "))
                add_element(set2, element)
            if is_subset(set1, set2):
                print("Set1 is a subset of Set2.")
            else:
                print("Set1 is not a subset of Set2.")
        elif choice == 10:
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
