import java.util.*;

public class DiscussionDirector {
	
	private Random rdm = new Random();
	private Agent agt1, agt2;
	
	public DiscussionDirector(){
		this.agt1 = Agent.generateAgent();		//creating the agents
		this.agt2 = Agent.generateAgent();}
	
	public Agent getAgt1(){return this.agt1;}
	public Agent getAgt2(){return this.agt2;}
	
	public void discussion(Agent a, Agent b){
		if (a.soc1(b)){ //<-----prints first section of test and decides first pathway through- 
								//the boolean return value
			if (!a.soc2(b)){ //decides second pathway 			//prints option 1
				if (a.soc3(a)) a.end1(b);		//other second pathways
				else a.end2(b);}}				//prints option 2
		else{ if (rdm.nextInt(10)<3) a.end2(b); //other option for first pathway 
				else a.end3(b);}}}				//and it's corresponding endings
