//just a simple string reverser
public class prac2
{
    public static void main(String[] args)
    {
        if (args.length == 0)
        {
            System.out.println("Incorrect number of arguments");
            return;
        }       

        String word = args[0];
        StringBuffer copy = new StringBuffer(word); //should always be a string buffer if need
        // to change the characters as strings are immutable so won't allow change
        copy.reverse();
        System.out.println("Reversed word is: "+copy);

    }
}