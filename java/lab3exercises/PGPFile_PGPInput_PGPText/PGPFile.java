import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;


/**
 * Wrapper class created for use in COMP1009 to simplify initial file I/O
 * @author jason.atkin@nottingham.ac.uk
 */
public class PGPFile
{
	public boolean openReadFile( String strFileName )
	{
		// Close any existing file before opening new one
		if ( br != null )
		{
			System.err.println("PGPFile.openReadFile: You opened a file for READ when there was already a file open for READ! (I will closing the open file first now...)");
			closeReadFile();
		}
		
		try 
		{
			br = new BufferedReader(
					new FileReader(strFileName));
	    }
		catch(Exception e )
		{
			System.err.println("PGPFile.openReadFile: Failed to open file for READ! " + e.toString() );
			return false;
		}
		return true;
	}

	public String readNextLine()
	{
		// If not open then we can't do this
		if ( br == null )
		{
			System.err.println("PGPFile.readNextLine: you must open the file for READ first before you can read from it!");
			return null;
		}

		try
		{
			return br.readLine();
		} 
		catch (IOException e)
		{
			System.err.println("PGPFile.readNextLine: error reading from file! " + e.toString() );
			return null;
		}
	}
	
	public boolean closeReadFile()
	{
		// If not open then we can't do this
		if ( br == null )
		{
			System.err.println("PGPFile.closeReadFile: You tried to close the READ file when it was not open.");
			return false;
		}
		
		try
		{
			br.close();
			br = null;
		} 
		catch (IOException e)
		{
			br = null;
			System.err.println("PGPFile.closeReadFile: Error closing READ file! " + e.toString() );
			return false;
		}
		return true;
	}
	
	public boolean openWriteFile( String strFileName )
	{
		// Close any existing file before opening new one
		if ( bw != null )
		{
			System.err.println("PGPFile.openWriteFile: You opened a file for WRITE when there was already a file open for WRITE!");
			closeWriteFile();
		}

		try
		{
	        bw = new BufferedWriter(new FileWriter(strFileName));
			return true;
	    } 
		catch (IOException e)
		{
			System.err.println("PGPFile.openWriteFile: Failed to open WRITE file! " + e.toString() );
			return false;
		}
	}

	public boolean writeLine( String strLine )
	{
		// If not open then we can't do this
		if ( bw == null )
		{
			System.err.println("PGPFile.writeLine: You must open the file for WRITE before you attempt to write to it!");
			return false;
		}

		try
		{
			bw.write( strLine + "\r\n" );
			return true;
		} 
		catch (IOException e)
		{
			System.err.println("PGPFile.writeLine: Error writing to output file! " + e.toString() );
			return false;
		}
	}
	
	public boolean closeWriteFile()
	{
		// If not open then we can't do this
		if ( bw == null )
		{
			System.err.println("PGPFile.closeWriteFile: You tried to close the WRITE file when it was not open!");
			return false;
		}
		
		try
		{
			bw.close();
			bw = null;
			return true;
		} 
		catch (IOException e)
		{
			bw = null;
			System.err.println("PGPFile.closeWriteFile: Error when trying to close to write file! " + e.toString() );
			return false;
		}
	}
	
	// Internal object - the reader for the input file
	protected BufferedReader br;
	// Internal object - the writer for the output file
	protected BufferedWriter bw;
}
