/******************************************************************************
 * On my honor, I pledge that I have neither received nor provided improper assistance 
 * in the completion of this programming assignment. Signed: Sungjin Lee
 * author : Sungjin Lee
 * date : 2014.03.28
 * description : Enter the number of consonants and 7 digits phone number and 
 * 						we can get conbined alphabet. 
 * input : number of consonants, 7 digits phone number
 * output : combined alphabet.
 ******************************************************************************/

/** 
 * Description: The provided program is to turn regular phone 
 * numbers into "words." For example, we may have a number 
 * 1-800-426-3664 that translated into 1-800-HANDONG. 
 * (When you try 356-9377 with five consonants, you will find 
 * ��flowers��, 232-6459 with four consonants ��afamily��.)  
 * The program, when working properly, will provide all possible 
 * "words" that have no more than a user-specified number of consonants. 
 * 
 * Author: Youngsup Kim
 * 03/15/2014	Creation 
 * 
 */
import javax.swing.JOptionPane;

public class Hw05_21300691_정원식 {
	public static void main(String[] args) {
		/***************************************************************************
		 * phoneString - stores the phone number entered by the user.
		 * 
		 * maxNumConsonant - User entered value that filters out those numbers
		 * with too many consonants.
		 * 
		 * goahead - true/false flag that determines whether or not the user
		 * wants to test another number.
		 ****************************************************************************/

		int maxNumConsonant;
		boolean goahead = true;

		while (goahead) {
			/* Gathers user data (1) maxNumConsonant: the maximum number of
			 * consonants (0 ~ 6). (2) phoneString: a 7 digit phone number The
			 * use of JOptionPane is illustrated here.
			 */
			String iString = JOptionPane
					.showInputDialog(
							null,
							"This program finds words that can be associated \n"
									+ "with phone numbers. \n"
									+ "(note: 0's and 1's are considered consonants) \n"
									+ "What is the maximum number of consonants \n"
									+ "you would like the generated word to possess?",
							"Debugging", JOptionPane.QUESTION_MESSAGE);
			if (iString == null)
				return;

			maxNumConsonant = Integer.parseInt(iString);
			if (maxNumConsonant > 6)
				return;

			String phoneString = JOptionPane.showInputDialog(null,
					"Enter a 7 digit phone number w/o dash?", "Debugging",
					JOptionPane.QUESTION_MESSAGE);
			if (phoneString == null)
				return;
			if (phoneString.length() < 7)
				return;

			/* The generateSpellings function does most of the work */
			generateSpellings(phoneString, maxNumConsonant); 

			if (JOptionPane.showConfirmDialog(null,
					"Would you like to try another number?", null,
					JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION)
				goahead = false;
		}
		return;
	}

	/***************************************************************************
	 * generateSpellings (String phoneString, int maxNumConsonant)
	 * 
	 * phoneByte The characters '1', '2', '3'... are converted to 1, 2, 3, 4...
	 * and stored appropriately in this numeric representation of the users
	 * phone number.
	 * 
	 * level This variable is used to make the printouts nice.
	 * 
	 * a-g Index variables used to keep track of for loops.
	 * 
	 * word A candidate "word" that is then passed on to printIfGood which
	 * prints the word if it meets the minimum requirements for consonants.
	 * 
	 * dial A 2-d array. For each dial [i][j], i represents the actual number on
	 * the key pad, and j stores a possible number that keypad could represent.
	 * So, for example, dial[2][3], could represent the third letter that "1" on
	 * the keypad represents... or in this case the letter "c." Similarly,
	 * dial[2][2] == 'b', dial [3][3] = f, etc. Confused? Pick up your phone and
	 * take a look! Some letters aren't mapped the way it should be. Note, the
	 * letters "q" and "z" have been removed. The numbers 0 and 1 have no
	 * associated letters and as such, the program simply returns a "1" or a "0"
	 * in those circumstances.
	 ****************************************************************************/

	// Declare generateSpellings as void type.
	public static void generateSpellings(String phoneString, int maxNumConsonant) {
		byte[] phoneByte = new byte[7];
		int a, b, c, d, e, f, g;
		int level = 0;
		//Declare 2-dimensioin array
		char[][] dial = { { '0', '0', '0' }, { '1', '1', '1' },
				{ 'a', 'b', 'c' }, { 'd', 'e', 'f' }, { 'g', 'h', 'i' },
				{ 'j', 'k', 'l' }, { 'm', 'n', 'o' }, { 'p', 'r', 's' },
				{ 't', 'u', 'v' }, { 'w', 'x', 'y' } };

		// Each ascii character stored in phoneString is converted to its
		// appropriate number.
		convertStringToByte(phoneString, phoneByte);

		/*
		 * The following for loop works as follows, for each of the seven digits
		 * in the phone number, we generate all the different possible letters
		 * each letter can take on by considering each digit in turn until all
		 * values are exhausted.
		 */

		for (a = 0; a < 3; a++) {
			for (b = 0; b < 3; b++) {
				for (c = 0; c < 3; c++) {
					for (d = 0; d < 3; d++) {
						for (e = 0; e < 3; e++) {
							for (f = 0; f < 3; f++) {
								for (g = 0; g < 3; g++) {
									/*
									 * The candidate word is built here.
									 * Starting with the first letter of the
									 * word we assign a candidate translation
									 * dial[][a] based on the original number's
									 * value.
									 */
									String word = "";
									word += dial[phoneByte[0]][a];
									word += dial[phoneByte[1]][b];
									word += dial[phoneByte[2]][c];
									word += dial[phoneByte[3]][d];
									word += dial[phoneByte[4]][e];
									word += dial[phoneByte[5]][f];
									word += dial[phoneByte[6]][g];

									// Print the word if it meets the minimum
									// requirements.
									//Enter the return value in level
									level=printIfGood(maxNumConsonant, word,
											level);
								}
							}
						}
					}
				}
			}
		}
	}

	// This function prints the word if it has maxNumConsonant or fewer
	// consonants
	private static int printIfGood(int maxNumConsonant, String word, int level) {
		
		//Initialize variable in zero
		int numVowel=0;

		// This loop counts the number of vowel.
		for (int i = 0; i < 7; i++)
			if (isVowel(word.charAt(i)))
				numVowel++;

		// This loop prints the word if there is maxNumConsonant or fewer
		// consonants.
		if ((7 - numVowel) <= maxNumConsonant) {
			//Change "println" to "print".
			System.out.print(word + " ");

			// Every time we print a word out, we add 1 to the value of level.
			level++;

			// Every seventh word we print out, we add a newline to make the
			// format nice.
			if ((level) % 7 == 0)
				System.out.print("\n");
		}
		return level;
	}

	// This function checks to see if the letter in question is a, e, i, o, u
	private static boolean isVowel(char x) {
		return ((x == 'a') || (x == 'e') || (x == 'i') || (x == 'o') || (x == 'u'));
	}

	/*
	 * This function converts each character in phoneString into numbers and
	 * places its contents into the array phoneByte
	 */

	private static void convertStringToByte(String phoneString,
			byte phoneByte[]) {
		for (int i = 0; i < 7; i++) {
			//Change the int type to the byte type.
			phoneByte[i] = (byte)(phoneString.charAt(i) - '0');
		}
	}

}