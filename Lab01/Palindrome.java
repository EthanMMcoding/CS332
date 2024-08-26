import java.util.Scanner;

public class Palindrome {

	public static boolean isPalindrome(String str) {
		int i, j;

		for (i = 0, j = str.length() - 1; i < str.length()/2; i++, j--) 
			if (str.charAt(i) != str.charAt(j)) 
				return false;

		return true;
	}

	public static void main(String[] args) {

		System.out.print("Enter a string: ");
		Scanner scan = new Scanner(System.in);
		String str =  scan.next();

		if (isPalindrome(str)) 
			System.out.println(str + " is a palindrome");
		else
			System.out.println(str + " is not a palindrome");
	}
}

