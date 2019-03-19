import java.util.ArrayList;

public class Sequence <T>{
	ArrayList<T> list;
	Integer current;
	
	//Create an empty Sequence Object with 
	//a size of 0 and the current index points to 0.
	public Sequence(){
		setList(new ArrayList<T>());
		setCurrentIndex(0);
	}
	
	//Takes a parameter T data and adds it
	//after the current index being pointed at
	//by current.
	public T addAfter(T data){
		if(list.size() <= 0){
			list.add(data);
		}else{
			list.add(current+1, data);
		}
		return list.get(current);
	}
	
	//Takes a parameter T data and adds it
	//before the current index being pointed at
	//by current.
	public T addBefore(T data){
		if(current-1 != -1){
			list.add(current-1, data);
			return list.get(current-1);
		}
		
		return list.get(current);
	}
	
	//Adds the list of addend to this list
	public void addAll (Sequence<T> addend){
		ArrayList<T> add = addend.getList();
		if(add == null){
			return;
		}
		
		for(T i : add){
			list.add(i);
		}
	}
	
	//Adds the lists of two Sequence obects into a new list
	public static <T> Sequence<T> concatenate(Sequence<T> list1, Sequence<T> list2) throws NullPointerException{
		Sequence <T> newList = new Sequence<T>();
		ArrayList<T> seq1 = list1.getList();
		ArrayList<T> seq2 = list2.getList();
		
		if(seq1 == null || seq2 == null){
			return null;
		}
		
		newList.addAll(list1);
		newList.addAll(list2);
		
		
		return newList;
	}
	
	//Remove the data at the current index and moves
	//the point to the next index if the current index is
	//not the last index.
	public T removeCurrent(){
		list.remove((int)current);
		if(list.size()-1 != current){
			current++;
		}else{
			current = null;
			return null;
		}
		
		return list.get(current);
	}
	
	//Moves the pointer one index forward given that
	//the pointer is not null and that the pointer is not
	//at the last index of the list.
	public void advance(){
		if(current != null){
			current++;
		}else{
			throw new IllegalStateException();
		}
		
		if(current > list.size()){
			current = null;
		}
	}
	
	//Checks to see if the pointer exists
	public boolean isCurrent(){
		return (current != null);
	}
	
	//Moves the pointer to index 0
	public void start(){
		if(list != null){
			setCurrentIndex(0);
		}
	}
	
	//Returns a clone of this object
	public Sequence<T> clone(){
		Sequence<T> clone;
		clone = this;
		 return clone;
	}
	
	//Returns the size of this Sequence's list
	public int size(){
		return list.size();
	}
	
	//Displays the data in the current Sequence
	public void displaySequence(){
		System.out.println("-----------------");
		for(T i : getList()){
			System.out.println(i.toString());
		}
		System.out.println("-----------------");
	}
	
	//Returns the data that the pointer is pointing at
	public T getDataAtCurrent(){
		return (T) list.get(current);
	}
	
	//Returns the list
	public ArrayList<T> getList(){
		return list;
	}
	
	//Returns the the position that is being pointed at
	public Integer getCurrentIndex(){
		return current;
	}
	
	//Sets the list to the parameter list
	public void setList(ArrayList<T> list){
		this.list = list;
	}
	
	//Sets the current index to the parameter index
	public void setCurrentIndex(int index){
		current = index;
	}
	
}
