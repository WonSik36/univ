/**	5 sites with their web site name in the first ten lines.
 *		http://www.google.org
 *		http://www.wikipedia.org
 *		http://www.wikimedia.org
 *		http://www.craigslist.org
 *		http://www.idealist.org
 *
 *	5 sites with no their name in the first ten lines.
 *		http://www.pir.org
 *		http://www.change.org
 *		http://www.acne.org
 *		http://www.wordpress.org
 *		http://www.mozilla.org
**/

import java.net.URL;
import java.io.*;
import java.lang.String;
import java.util.Scanner;

public class OpenOrg213691Á¤¿ø½Ä {

	public static void main(String[] args) throws Exception{
			BufferedReader keyboard;
			String inputLine;
			keyboard = new BufferedReader(new InputStreamReader(System.in));
			System.out.print("Enter the name of a organization (w/o spaces): ");
			System.out.flush(); // Make sure the line is printed immediately.
			inputLine = keyboard.readLine();
			System.out.println(inputLine);
			
			try{
				boolean isExist = false;
				String result = "first line number which contain (" + inputLine + ") is ";
				String[] statement = new String[10];
				String address = "http://www." + inputLine.trim() + ".org/";
				URL url = new URL(address);
				Scanner input = new Scanner(url.openStream());
			
				for(int i=0; i<statement.length; i++){
					statement[i] = input.nextLine();
					for(int j=0; j<statement[i].length()-inputLine.length(); j++){
						if(isExist!=true && inputLine.equalsIgnoreCase(statement[i].
								substring(j, j + inputLine.length()))){
							result += (i+1);
							isExist = true;
							break;
						}
					}
				}
				for(int i=statement.length-1; i>=0; i--)
					System.out.println(statement[i]);
				
				if(isExist)
					System.out.println(result);
				else
					System.out.println("there is no matching line in the first 10 lines.");
			}
			catch (java.net.UnknownHostException ex){
				System.out.println("Internet is not connected");
				throw ex;
			}
			catch (java.net.MalformedURLException 
					| java.util.NoSuchElementException ex){
				System.out.println("Invalide URL");
				throw ex;
			}
			catch (IOException ex){
				System.out.println("I/O Errors: no such file");
				throw ex;
			}
	}
}