import java.util.Random;
public class ArrayUtilities {
	
	public static boolean linearSearch(int[]array, int target){
		int arrL = array.length;
		for (int i=0; i<arrL; i++){
			if(array[i]==target) return true;}
		return false;}
	
	public static boolean binarySearch(int[]array, int target){ 
		int left = 0;
		int right = array.length-1;
		while(left<=right){
			int middle = (left+right)/2;
			if (array[middle] == target) return true;
			if (array[middle] >= target) right = middle-1;
			if (array[middle] <= target) left = middle+1;}
		return false;
	}
	
	public static int [] copy(int array []){
		int size = array.length;
		int[] mime = new int[size];
		for (int i = 0; i<size; i++){
			mime[i] = array[i];}
		return mime;}
	
	public static void sort(int[] array){
		int size = array.length;
		for (int i = 0; i<size; i++){
			for (int j = i+1; j<size; j++){
				if (array[i]>array[j]){
					int a = array [i];
					int b = array [j];
					array[i] = b;
					array[j] = a;}}}}
	
	public static int[] generateRandom(int n){
		int[] array = new int[n];
		Random val = new Random(1);
		for (int i = 0; i<n; i++){
			array[i] = val.nextInt(Integer.MAX_VALUE);}
		return array;}

}
