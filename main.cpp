#include <iostream>
#include <string>
#include <limits>         //included for using std::numericlimits (line 94)

struct Book
{
    std::string title{}; //I like using brace init. to avoid unwanted conversions
    std::string author{}; //and to keep the init. style constant
    std::string id{};
    int daysBorrowed{};
};

int penalty(const Book &book); //pass by reference as to avoid expensive copies of struct Book

int main()
{
    const int nrBooksBorrowed{100};    //const so as not to be changed accidentally later
    Book sheetBorrowed[nrBooksBorrowed];    //used C-style arrays, so I gave an arbitrary value to the array

    for (int i{0}; i < nrBooksBorrowed; i++)   //for loop for init. the array
    {
        std::cout << "Enter the book's title: ";
        std::getline(std::cin, sheetBorrowed[i].title);          //std::getline for capturing the white spaces too
        std::cout << "Enter the book's author: ";
        std::getline(std::cin, sheetBorrowed[i].author);          //each index (meaning each element of the array of structs)
        std::cout << "Enter the book's ID: ";           //gets data from the user
        std::getline(std::cin, sheetBorrowed[i].id);
        std::cout << "Enter the number of days the book has been borrowed: ";
        std::string str_daysBorrowed{};                        //variable to get the number of days borrowed from the user
        std::getline(std::cin, str_daysBorrowed);
        sheetBorrowed[i].daysBorrowed = std::stoi(str_daysBorrowed);     //std:stoi for conversion from string to int

        std::cout << "\nDo you want to enter another book (yes/no): ";   //code asks if the user wants to add more books or not
        std::string answer{};
        std::getline(std::cin, answer);
        if (answer == "no")
            break;
        std::cout << '\n';
    }

    std::cout << '\n';  //aesthetic role

    for (int i{0}; i < nrBooksBorrowed; i++)      //for loop for showing books the user entered
    {
        if (!sheetBorrowed[i].title.empty())        //function to stop the loop at the last book entered
        {                                      //(the array has memory allocated for 100 elements
            std::cout << sheetBorrowed[i].title << " - " << sheetBorrowed[i].author << ", "
            << sheetBorrowed[i].id << ", " << sheetBorrowed[i].daysBorrowed << " days\n";
        }
    }

    std::cout << '\n';

    int i{};   //here is the beginning of the main menu
    do
    {
        std::cout << "1. Calculate Penalty\n" << "2. Return Book\n" << "3. Exist\n" << "Choose an option: ";
        std::cin  >> i;
        std::cout << '\n';

        if (i < 1 || i > 3) //forcing the user to enter only valid options
        {
            std::cout << "Please choose a valid option.\n";
        }

        if (i == 1)
        {
            std::cout << "The user's sheet of borrowed books includes the following: \n";
            for (int ii {0}; ii < nrBooksBorrowed; ii++)    //shows the user's books
            {
                if (!sheetBorrowed[ii].title.empty())    //same as on line 45
                {
                    std::cout << sheetBorrowed[ii].title << " - " << sheetBorrowed[ii].author << ", "
                    << sheetBorrowed[ii].id << ", " << sheetBorrowed[ii].daysBorrowed << " days\n";
                }
            }

            int result{0};   //for loop that calls penalty() and calculates the total
            for (int counter = 0; counter < nrBooksBorrowed; counter++)
            {
                if (!sheetBorrowed[counter].title.empty())
                {
                    result += penalty(sheetBorrowed[counter]);
                }
            }
            std::cout << "The penalty is: " << result << " Euros\n";
        }

        if (i == 2)     //for returning books to the library
        {
            for (int i = 0; i < nrBooksBorrowed; i++)
            {
                std::string deleteID{};
                std::cout << "Enter the book's ID: \n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, deleteID);

                for (int j = 0; j < nrBooksBorrowed; j++)       //for loop to traverse through all the user's books
                {
                    if (deleteID == sheetBorrowed[j].id)
                    {
                    sheetBorrowed[j] = {"0", "0", "0", 0};   //because C-style arrays are not dynamically allocated and don't have functions like pop.back()
                    std::cout << "The book with the ID " << deleteID << " has been returned.\n";
                    deleteID = {};  //reset so as to be used later
                    break;
                    } else if (j == nrBooksBorrowed - 1)    //if the books ID wasn't found, print error message
                      {
                        std::cout << "Please enter a valid ID.\n";
                        deleteID = {};
                        break;
                      }
                }

                break;
            }
        }

        std::cout << '\n';

    }while(i != 3);     //if the user enters '3', the program stops

    return 0;
}

int penalty(const Book &book)
{
    int value{};
    if (book.daysBorrowed <= 14) //no penalty for 14 days borrowed
        value = value + 0;
    else if (book.daysBorrowed > 14)
    {
        int x{book.daysBorrowed - 14};
        value = value + x;
    }
    return value * 5;     //5 Euro penalty for each day of being late
}
