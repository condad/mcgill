public class StopWatch {
	
	private long startTime;
	private long stopTime;
	
	public void start(){
		startTime = System.nanoTime();}
	
	public void stop(){
		stopTime = System.nanoTime();}
	
	public long getTimeNano(){
		return stopTime-startTime;}
	
	public long getTimeMicro(){
		return (stopTime-startTime)/1000;}
	
	public long getTimeMilli(){
		return (stopTime-startTime)/1000000;}
	
	public long getTimeSeconds(){
		return (stopTime-startTime)/1000000000;}
	
}
