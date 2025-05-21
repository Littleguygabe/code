import java.util.ArrayList;

/**
 * Wrapper class created for use in COMP1009 to simplify storing of multiple lines of text (e.g. from a file)
 * @author jason.atkin@nottingham.ac.uk
 */
public class PGPText
{
	public PGPText()
	{
		internalArray = new ArrayList<String>();
	}
	
	public void addLine( String strText )
	{
		internalArray.add(strText);
	}
	
	public String getLine( int iLine )
	{
		return internalArray.get(iLine);
	}

	public void setLine( int iLine, String strText )
	{
		while ( iLine >= internalArray.size() )
			internalArray.add("");
		internalArray.set(iLine, strText);
	}

	public int getLineCount()
	{
		return internalArray.size();
	}
	
	// A standard collection class
	protected ArrayList<String> internalArray;
}
