class StringOperations:
    
    def __init__(self, string):
        self.string = string

    # To display the word with the longest length
    def longest_word(self):
        words = self.string.split()
        longest = max(words, key=len)
        return longest

    # To determine the frequency of occurrence of a particular character in the string
    def char_frequency(self, char):
        return self.string.count(char)

    # To check whether the given string is a palindrome or not
    def is_palindrome(self):
        cleaned_string = ''.join(e for e in self.string if e.isalnum()).lower()  # Ignore spaces and case
        return cleaned_string == cleaned_string[::-1]

    # To display index of the first appearance of the substring
    def first_substring_index(self, substring):
        return self.string.find(substring)

    # To count the occurrences of each word in a given string
    def word_count(self):
        words = self.string.split()
        word_frequency = {}
        for word in words:
            word_frequency[word] = word_frequency.get(word, 0) + 1
        return word_frequency

# Get user input for the string
user_input_string = input("Enter a string: ")

# Create an object of StringOperations class with the user's string
string_operations = StringOperations(user_input_string)

# Display the word with the longest length
print("Longest word:", string_operations.longest_word())

# Get user input for the character to determine its frequency
char = input("Enter a character to find its frequency: ")
print(f"Frequency of '{char}':", string_operations.char_frequency(char))

# Check whether the given string is a palindrome or not
print("Is palindrome:", string_operations.is_palindrome())

# Get user input for the substring to find its first occurrence
substring = input("Enter a substring to find its first occurrence: ")
print(f"Index of the first appearance of '{substring}':", string_operations.first_substring_index(substring))

# Count the occurrences of each word in the given string
print("Word count:", string_operations.word_count())