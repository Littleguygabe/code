//just a simple string character incrementer
public class lab1prac1 {
    public static void main(String[] args) 
    {
        String word = "Hello World";
        if (args.length > 0) //function length is applied directly to the
                             // the object we want to get the length of
        {
            word = args[0]; //java doesnt take the first argument as the 
                            //as the name of the program like in C
        }

        StringBuffer copy = new StringBuffer(word); //creates a copy of the
        // word into the new variable copy

        int i =0;
        while (i<copy.length()) //loops through the length of the copied word
        {
            char c = copy.charAt(i); //gets the character at the current index within copy
            copy.setCharAt(i, (char)(c+1)); // then converts the char
            // to be the next character in the alphabet

            // automatically takes the character value as an integer so need
            // to perform type cast to char which allows us to add 1 to it


            i++; //incrememnts the counter for the loop
        }

        System.out.println(copy); //prints the modified copy

    }
}

