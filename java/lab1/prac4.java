//A simple decrypter that takes 2 arguments - 1st is the word to be encrypted, 2nd is the key
public class prac4 
{
    public static void main(String[] args) 
    {
        if (args.length != 2)
        {
            System.out.println("Incorrect number of arguments");
            return;
        }
        
        StringBuffer copy = new StringBuffer(args[0]);
        StringBuffer decrypted = decrypt(copy,args[1]);
        System.out.println("Decrypted word: " + decrypted);

    }

    public static StringBuffer decrypt(StringBuffer copyOfWord, String key)
    {
        int m=0;
        int p=0;
        while (m<copyOfWord.length())
        {
            char c = copyOfWord.charAt(m);
            char pChar = key.charAt(p);
            copyOfWord.setCharAt(m, (char)((50+(c&0x9F)-(pChar&0x9F))%26));
            m++;
            p++;
            if (p==key.length())
            {
                p=0;
            }
        }
        return copyOfWord;
    }

}