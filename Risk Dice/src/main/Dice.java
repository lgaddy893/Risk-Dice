/**
 * 
 */
package main;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;
import java.util.Scanner;

/**
 * @author Landon Gaddy
 *
 */
public class Dice {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Random rand = new Random();
		Scanner scan = new Scanner(System.in);
		ArrayList<Integer> attack;
		ArrayList<Integer> defend;
		while(true) {
			try {
				System.out.println("Attack Dice: ");
				int a = scan.nextInt();
				attack = new ArrayList<Integer>();
				for(int i = 0; i < a; i++) {
					attack.add(rand.nextInt(6)+ 1);
				}
				System.out.println("Defense Dice: ");
				int d = scan.nextInt();
				defend = new ArrayList<Integer>();
				for(int i = 0; i < d; i++) {
					defend.add(rand.nextInt(6) + 1);
				}
				Collections.sort(attack, Collections.reverseOrder());
				Collections.sort(defend, Collections.reverseOrder());
				int low = attack.size() > defend.size() ? defend.size(): attack.size();
				int dl = 0;
				int al = 0;
				System.out.println("a v. d");
				for ( int i = 0; i < low; i++) {
					System.out.println(attack.get(i) + " vs " + defend.get(i));
					if (attack.get(i) > defend.get(i)) {
						dl++;
					} else {
						al++;
					}
				}
				System.out.println("Attack Loses: " + al + " Defence Loses: " + dl);
				System.out.println();
			} catch(Exception e) {
				System.out.println("Something bad happened");
			}
			
		}
	}

}
