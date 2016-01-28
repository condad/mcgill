import java.util.Arrays;
public class SearchComparison {

	public static void main(String[] args) {
		int n = 10;
		while (n<=500000000){
			System.out.print(n+", ");
			StopWatch watch =  new StopWatch();
			
			watch.start();
			int[] array = ArrayUtilities.generateRandom(n);
			watch.stop();
			System.out.print(watch.getTimeMicro()+", ");
			
			watch.start();
			ArrayUtilities.linearSearch(array, -1);
			watch.stop();
			System.out.print(watch.getTimeMicro()+", ");

			watch.start();
			int[] nw = ArrayUtilities.copy(array);
			watch.stop();
			System.out.print(watch.getTimeMicro()+".0" + ", ");

			watch.start();
			ArrayUtilities.sort(array);
			watch.stop();
			System.out.print(watch.getTimeMicro()+", ");
			
			watch.start();
			Arrays.sort(nw);
			watch.stop();
			System.out.print(watch.getTimeMicro()+", ");
			
			watch.start();
			ArrayUtilities.binarySearch(array, -1);
			watch.stop();
			System.out.println(watch.getTimeMicro());
			n = n*2;}}

}
