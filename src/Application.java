import java.util.ArrayList;

public class Application {
	static Sequence<Integer> series;
	static ArrayList<Integer> list;
	
	public static void main(String[] args) {
		series = new Sequence<Integer>();
		list = series.getList();
		Sequence<Integer> clone;
		Sequence<Integer> testList1 = new Sequence<Integer>();
		Sequence<Integer> testList2 = new Sequence<Integer>();
		
		print(series);

		series.addAfter((int)(Math.random()*1000));
		series.addAfter((int)(Math.random()*1000));
		series.addAfter((int)(Math.random()*1000));
		series.addAfter((int)(Math.random()*1000));
		series.addAfter((int)(Math.random()*1000));
		
		print(series);
		
		System.out.println("\nCurrent Series:");
		series.displaySequence();
		
		series.setCurrentIndex(1);
		series.addAfter((int)(Math.random()*1000));
		
		System.out.println("\nMoving Cursor and Adding After: " + series.getDataAtCurrent());
		print(series);
		
		series.addBefore((int)(Math.random()*1000));
		System.out.println("\nAdded Before: " + series.getDataAtCurrent());
		print(series);
		series.addBefore((int)(Math.random()*1000));
		System.out.println("\nAdded Before " + series.getDataAtCurrent());
		print(series);
		
		System.out.println("\nAdd Before Series:");
		series.displaySequence();
		
		series.setCurrentIndex(6);
		series.removeCurrent();
		
		System.out.println("\nIndex 6 removed:");
		print(series);
		
		clone = series.clone();
		
		System.out.println("\nClone Sequence: ");
		clone.displaySequence();
		
		System.out.println("\nAre the objects the same?");
		System.out.println((clone == series));
		
		series.setCurrentIndex(1);
		clone.setCurrentIndex(1);
		
		System.out.println("\nAre the indexs the same?");
		System.out.println(series.getCurrentIndex() == clone.getCurrentIndex());
		
		testList1.addAfter((int)(Math.random()*1000));
		testList1.addAfter((int)(Math.random()*1000));
		testList1.addAfter((int)(Math.random()*1000));
		testList1.addAfter((int)(Math.random()*1000));
		testList1.addAfter((int)(Math.random()*1000));
		
		System.out.println("\nList 1:");
		print(testList1);
		
		testList2.addAfter((int)(Math.random()*1000));
		testList2.addAfter((int)(Math.random()*1000));
		testList2.addAfter((int)(Math.random()*1000));
		testList2.addAfter((int)(Math.random()*1000));
		testList2.addAfter((int)(Math.random()*1000));
		
		System.out.println("\nList 2:");
		print(testList2);
		
		series.addAll(testList1);
		
		System.out.println("\nSeries + List 1:");
		print(series);
	
		series = (Sequence<Integer>) Sequence.concatenate(series, testList2);
		
		System.out.println("\nNew Series + List 2:");
		print(series);
		
		System.out.println("\nSeries + List 1 + List 2:");
		series.displaySequence();
		
		series.start();
		System.out.println("\nDo we have a pointer: " + series.isCurrent());
		print(series);
		
		System.out.println("\nMove up");
		series.advance();
		print(series);
		
		System.out.println("\nMove up");
		series.advance();
		print(series);
		
		System.out.println("\nMove up");
		series.advance();
		print(series);
		
		System.out.println("\nTo the end");
		series.setCurrentIndex(series.size()-1);
		print(series);
		
		series.advance();
		System.out.println("\nAdvance");
		print(series);
		
		series.advance();
		System.out.println("\nAdvance");
		print(series);
		
		System.out.println("\nIn bounds?");
		System.out.println(series.isCurrent());
	}
	
	public static void print(Sequence<Integer> list){
		System.out.println("Size: " + list.size() + " Current: " + list.getCurrentIndex());
	}
}
