import java.util.*;
import java.io.*;

public class Agent {
	
	private final String[] files = {"MaleNames.txt", "Cities.txt", "Majors.txt"}; 
	private Random rdm = new Random();
	private String name, hometown, city, major;
	private boolean isMale;
	private int bday, bmonth, byear;
	private final String[] months = {"January","February","March","April","May",
						"June","July","August","September","October","November","December"};
	
	public Agent(){
		this.bday = rdm.nextInt(30)+1;      //initializing birthday
		this.bmonth = rdm.nextInt(11);							//month
		this.byear = rdm.nextInt(200)+1800;								//year
		
		if (rdm.nextInt(10)>=5) this.isMale = true;   //initializing gender
		else {this.isMale = false; files[0] = "FemaleNames.txt";} //changes the files array for female names
		
		//this loop gets a random word from each of the relevant files
		for (int i=0; i<files.length; i++){				
			try{if(i==0) this.name = new WordList(files[i]).getRandomWord();
					if(i==1) {this.hometown = new WordList(files[i]).getRandomWord();
								this.city = new WordList(files[i]).getRandomWord();}
						if(i==2) this.major = new WordList(files[i]).getRandomWord();}
			catch(IOException e){
				System.out.println(files[i]+" file was not found!");
				this.name = "(defaultname)"; this.hometown = "(defaulthometown)";
				this.city = "(defaultcity)"; this.major = "(defaultmajor)";}}}
	
	public static Agent generateAgent(){
		Agent rdmAgent = new Agent();
		return rdmAgent;}
	
	public void whoAreYou(){
		System.out.println( "My Name is "+ this.getName()+ "." + " *"+this.getGender()+"*");
		System.out.println("I was born in "+ this.getCityBorn() +" on "+this.getBirthday());
		System.out.print("I'm "+ this.howOldAreYou()+" years old. ");
		System.out.println("I live in "+ this.getCityNow() +".");
		System.out.println("I'm majoring in "+ this.getMajor()+ ".");}
	public String howOldAreYou(){
		int x = Calendar.getInstance().get(Calendar.YEAR)-byear;
		if((Calendar.getInstance().get(Calendar.MONTH)-bmonth) >=0){
			if((Calendar.getInstance().get(Calendar.DATE)-bday) >=0) return String.valueOf(x);
			else return String.valueOf(x--);}
		else return String.valueOf(x--);}
	
	public String getBirthday(){
		String dy = String.valueOf(bday);
		String yr = String.valueOf(byear);
		return months[bmonth]+ " "+dy + ", " + yr+".";}
	public String getGender(){
		if (isMale==true) return "male";
		else return "female";}
	public String getMajor(){return this.major;}
	public String getName(){return this.name;}
	public String getCityNow(){return this.city;}
	public String getCityBorn(){return this.hometown;}
	
	/* The following methods each represent an initial path of the DAG,
	 * They return booleans to decide the next pathway but still print
	 * their corresponding lines while being evaluating*/
	public boolean soc1(Agent a){
		//this method initiates the conversation and decides the first pathway using a rdm number
		System.out.println(this.getName()+" says: Hello my name is "+this.getName());
		if(rdm.nextInt(2)==0){System.out.println(a.getName()+" says. Hi "+this.getName()+". " +
				"My name is "+ a.getName()+". I feel really sleepy today.");
				return true;}
		else {System.out.println(a.getName()+" says: How's it going "+this.name+"?");
				System.out.println(this.getName()+" says: Fine thanks, where are " +
						"you from "+a.getName()+"?");	
				System.out.println(a.getName()+" says: I am from "+a.getCityBorn()+", but" +
						" I live in "+a.getCityNow()+" nowadays.");
				System.out.println(this.getName()+" says: I don't like people from "+a.getCityBorn());
				return false;}}
	
	public boolean soc2(Agent a){
		System.out.println(this.getName()+" says: Well "+a.getName()+", I don't really care " +
				"that you're sleepy.");
		if(rdm.nextInt(2)==0)System.out.println(a.getName()+" says: Well I don't really care if you don't care!");
		else System.out.println(a.getName()+" says: That's not very nice");
		System.out.println(this.getName()+" says: Whatever, goodbye "+a.getName()+".");
		if (rdm.nextInt(10)<2) return true;
		else return false;}
	
	public boolean soc3(Agent a){
		System.out.println(this.getName()+" says: Why are you so sleepy "+a.getName()+"?");
		System.out.println(a.getName()+" says: Because I just flew back from "+a.getCityBorn()+" last night.");
		System.out.println(this.getName()+" says: Good thing you left, "+a.getCityBorn()+" is a boring place.");
		if (rdm.nextInt(10)<3) return true;
		else return false;}
	//these methods finish the conversation
	public void end1(Agent a){
		System.out.println(a.getName()+" says: Talking to you is boring "+this.getName()+". Adios!");}
	
	public void end2(Agent a){
		System.out.println(a.getName()+" says: Thats rude, I'm going home.");}
	
	public void end3(Agent a){
		System.out.println(a.getName()+" says: I'm the only person you've ever meant from "+a.getCityBorn()+".");
		System.out.println(this.getName()+" says: Well I guess its just you i don't like then.");
		System.out.println(a.getName()+" says: "+this.getName()+"? What kind of name is that? I hate you "+this.getName()+".");
		System.out.println(this.getName()+" says: Whatever, "+a.getMajor()+" is a stupid subject! Goodbye.");}}
	
