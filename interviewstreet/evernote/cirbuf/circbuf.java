import java.util.*;
import java.lang.*;
import java.math.*;

public class circbuf {
	/*
	private class Node {
      private String data;
      private Node next;
  }

	private Node first;
	private Node last;
	private int N, size;
	
	public circbuf (int size){
		this.first = null;
		this.last = null;
		this.N = 0;
		this.size = size;
	}
	
	public boolean isEmpty() {
		return (first == null && N == 0) ;
	}
	
	public void insert(String data) {
		Node node = new Node ();
		node.data = data;
		node.next = null;
		if(isEmpty()){
			first = last = node;
		} else {
				if(N == size){
					System.out.println("N == size "+N);
				}else{
					first.next = node;
					first = node;
			}
		}
		N++;
		System.out.println("insert "+N+" "+data);
	}

	public void remove() {
		if(last != null){
			String data = last.data;
			last = last.next;
			N--;
			System.out.println("remove "+N+" "+data);
		}
	}

	public int currentSize() {
		return N;
	}
	
	public void printCB() {
		Node current = last;
		System.out.println("printCB ");
		while(current != first) {
			System.out.println(current.data);
			current = current.next;
		}
		System.out.println(current.data);
	}
	*/
	
	private String[] buffer;
	private int head, tail;
	private int N, size;
	private boolean crossed_head, crossed_tail;

	public circbuf (int size){
		this.head = 0; // data leaves
		this.tail = 0; // data enters
		this.N = 0;
		this.size = size;
		this.crossed_head = false;
		this.crossed_tail = false;
		buffer = new String[size];
	}
	
	public void insert(String data) {
      buffer[tail++] = data;
			System.out.println("insert at "+(tail-1)+" "+data);
      if (tail == size) {
				crossed_tail = !crossed_tail;
        tail = 0;
      }
			if(crossed_tail != crossed_head){
				if(tail > head)
					head = tail;
			}
	}
	
	public boolean isEmpty() {
		if(crossed_tail == crossed_head && tail == head ) return true;
		return false;
	}
	
	public void remove() {
		if(!isEmpty()){
      String data = buffer[head++];
			System.out.println("removed at "+(head-1)+" "+data);
      if (head == size) {
				crossed_head = !crossed_head;
        head = 0;
      }
		}
	}

	public void printCB() {
		int i = 0;
		if(crossed_head == crossed_tail){
			for(i=head;i<tail;i++)
				System.out.println(buffer[i]);
		} else {
			i = head;
			while(i < size) {
				System.out.println(buffer[i]);
				i++;
			}
			i=0;
			while(i < tail) {
				System.out.println(buffer[i]);
				i++;
			}			
		}
		
	}	
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		sc.nextLine();
		
		int i,n;
		String data, line;
		circbuf cb = new circbuf(N);
		
		while(true) {
			line = sc.nextLine();
			if (line.equals("Q")){
				break;
			} else {
				Scanner sc1 = new Scanner(line);
				char c = sc1.next().charAt(0);
			
				if( c == 'A') {
					n = sc1.nextInt();
					for(i=0;i<n;i++){
						data = sc.nextLine();
						cb.insert(data);
					}
				} else if( c == 'R') {
					//remove from list
					n = sc1.nextInt();
					for(i=0;i<n;i++){
						cb.remove();
					}			
				} else if( c == 'L') {
					//print the list
					cb.printCB();
				}
			}
		}
		
	}
}