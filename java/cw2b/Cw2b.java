package cw2b;
import java.util.ArrayList;

public class Cw2b extends BaseClass
{
 
    public ArrayList<String> movement;
    public ArrayList<String> noises;   

    public Cw2b()
    {
        this.movement = new ArrayList<>();
        this.noises = new ArrayList<>();
    }

    @Override
    public void createAnimals()
    {
        storeAnimal(new Fish());
        storeAnimal(new Fish());
        storeAnimal(new Bear());
        storeAnimal(new Bear());
        storeAnimal(new Lion());
        storeAnimal(new Bird());
    }

    @Override
    public void recordMadeSound( String str )
    {
        System.out.println(str);
        noises.add(str);
    }

    @Override
    public void recordMoved( String str )
    {
        System.out.println(str);
        movement.add(str);
    }

    @Override
    public void finish()
    {
        PGPFile fileObj = new PGPFile();
        fileObj.openWriteFile("output.txt");
        fileObj.writeLine("List of noises made:");

        for (String noise:noises)
        {
            fileObj.writeLine(noise);
        }
        fileObj.writeLine("List of movement made:");

        for (String move:movement)
        {
            fileObj.writeLine(move);
        }

        fileObj.closeWriteFile();   
    }

}