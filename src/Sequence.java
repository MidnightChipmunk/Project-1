import java.util.ArrayList;

public class Sequence <T>{
	ArrayList<T> list;
	boolean currentExists;
	int current;
	
	public Sequence(){
		setList(new ArrayList<T>());
		setCurrentIndex(0);
		currentExists = true;
	}
	
	public T addAfter(T data){
		list.add(current+1, data);
		return list.get(current+1);
	}
	
	public T addBefore(T data){
		if(current-1 != -1){
			list.add(current-1, data);
			return list.get(current-1);
		}
		
		return list.get(current);
	}
	
	public void addAll (ArrayList<T> addend){
		if(addend == null){
			return;
		}
		
		for(T i : addend){
			list.add(i);
		}
	}
	
	public static <T> ArrayList<T> concatenate(ArrayList<T> list1, ArrayList<T> list2) throws NullPointerException{
		ArrayList<T> newList = new ArrayList<T>();
		
		if(list1 == null || list2 == null){
			return null;
		}
		
		newList.addAll(list1);
		newList.addAll(list2);
		
		
		return newList;
	}
	
	public T removeCurrent(){
		list.remove(current);
		if(list.size()-1 != current){
			current++;
		}else{
			currentExists = false;
			return null;
		}
		
		return list.get(current);
	}
	
	public void advance(){
		if(currentExists){
			current++;
		}else{
			throw new IllegalStateException();
		}
	}
	
	public boolean isCurrent(){
		return currentExists;
	}
	
	public void start(){
		if(list != null){
			setCurrentIndex(0);
		}
	}
	
	@SuppressWarnings("unchecked")
	public Sequence<T> clone(){
		Sequence<T> ans;
		
		try{
			ans = (Sequence<T>)super.clone();
		}catch(CloneNotSupportedException exc){
			throw new RuntimeException("Can't clone!");
		}
		
		return ans;
	}
	
	public int size(){
		return list.size();
	}
	
	public void displaySequence(){
		for(T i : getList()){
			System.out.println(i.toString());
		}
	}
	
	public ArrayList<T> getList(){
		return list;
	}
	
	public int getCurrentIndex(){
		return current;
	}
	
	public void setList(ArrayList<T> list){
		this.list = list;
	}
	
	public void setCurrentIndex(int index){
		current = index;
	}
	
}
