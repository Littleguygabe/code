//A simple encrypter that takes 2 arguments - 1st is the word to be encrypted, 2nd is the key
public class prac3
{
    public static void main(String[] args)
    {
        if (args.length != 2)
        {
            System.out.println("Incorrect number of arguments");
            return;
        }
        
        StringBuffer copyOfword = new StringBuffer(args[0]);
        StringBuffer encrypted = encrypt(copyOfword,args[0],args[1]);
        System.out.println("Encrypted word is: "+encrypted);
        
    }

    public static StringBuffer encrypt(StringBuffer copyOfword,String word, String key)
    {
        int m=0;
        int p=0;
        while (m<copyOfword.length())
        {
            char c = copyOfword.charAt(m);
            char pChar = key.charAt(p);
            copyOfword.setCharAt(m, (char)(65+((c&0x9F)+(pChar&0x9F))%26));
            m++;
            p++;
            if (p==key.length())
            {
                p=0;
            }
        }
        return copyOfword;
    }
}