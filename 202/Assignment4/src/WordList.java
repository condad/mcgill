import java.io.*;
import java.util.*;

public class WordList {
	
	private BufferedReader br = null;
	private ArrayList<String> words = new ArrayList<String>();
	static Random rdm = new Random();
	
	public WordList(String filename) throws IOException{
		br = new BufferedReader(new FileReader(filename));
		String line = br.readLine(); 
		while (line != null) 
			{words.add(line);
            line = br.readLine();}
        br.close();}
	
	public String getRandomWord(){
		int index = rdm.nextInt(words.size());
		return words.get(index);}
	
	static int x = 3;
	static int y = 4;
	static double test = 4/3+4/3;
	
	public static void main(String[] args) {
		
		//DiscussionDirector test = new DiscussionDirector();
		//test.discussion(test.getAgt1(), test.getAgt2());
		System.out.println(test);}}
