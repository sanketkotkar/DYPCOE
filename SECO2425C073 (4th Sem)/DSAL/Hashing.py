# Initialize hash table
hash_table = [None] * 10

def hash_function(value):
    return value % 10

def insert(value):
    index = hash_function(value)
    if hash_table[index] is None:
        hash_table[index] = []
    for i in range(len(hash_table[index])):
        if hash_table[index][i] == value:
            hash_table[index][i] = value
            return f"Value {value} replaced at index {index}."
    hash_table[index].append(value)
    return f"Value {value} inserted at index {index}."

def delete(value):
    index = hash_function(value)
    if hash_table[index] is not None:
        for i in range(len(hash_table[index])):
            if hash_table[index][i] == value:
                hash_table[index].pop(i)
                return "Value " + str(value) + " deleted."
    return "Value " + str(value) + " not found."

def search(value):
    index = hash_function(value)
    if hash_table[index] is not None:
        for v in hash_table[index]:
            if v == value:
                return "Value " + str(value) + " found at index " + str(index) + "."
    return "Value " + str(value) + " not found."

def display():
    for i in range(len(hash_table)):
        print("Index", i, ":", hash_table[i])

def main():
    while True:
        print("\nHash Table Operations Menu:")
        print("1. Insert value")
        print("2. Delete value")
        print("3. Search value")
        print("4. Display hash table")
        print("5. Exit")
        choice = int(input("Enter your choice: "))

        if choice == 1:
            value = int(input("Enter value to insert: "))
            print(insert(value))
        elif choice == 2:
            value = int(input("Enter value to delete: "))
            print(delete(value))
        elif choice == 3:
            value = int(input("Enter value to search: "))
            print(search(value))
        elif choice == 4:
            print("Current hash table:")
            display()
        elif choice == 5:
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
