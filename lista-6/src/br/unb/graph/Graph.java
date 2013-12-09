package br.unb.graph;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class Graph {
	
	private ArrayList<Node> nodeList;
	private int adjacencyMatrix[][];
	
	private static final int MAX_NODES = 100;
	
	public Graph() {
		adjacencyMatrix = new int[MAX_NODES][MAX_NODES];
		nodeList = new ArrayList<Node>();
	}
	
	public int getListSize(){
		return nodeList.size();
	}
	
	public void addNode(String label){
		if(nodeList.size() <= MAX_NODES)
			nodeList.add(new Node(label, nodeList.size()));
		else 
			System.out.println("The graph is full. Max of allowed nodes is '"+ MAX_NODES +"'");
	}
	
	public void addEdge(int aIndex, int bIndex) {
		adjacencyMatrix[aIndex][bIndex] = 1;
		adjacencyMatrix[bIndex][aIndex] = 1;
	}
	
	void printNode(int index){
		System.out.println("Node "+ index +" - "+ nodeList.get(index).getLabel());
	}
	
	/* */
	
	public void breadthFirstSearch(){
		
		Queue<Node> bfsQueue;
		Node first, n, adj;
		int i;
		
		bfsQueue = new LinkedList<Node>();
		
		while( (first = getFirstUnvisited()) != null){
			bfsQueue.add(first);
			first.setVisited(true);
			
			while(!bfsQueue.isEmpty()){	
				n = bfsQueue.remove();
				
				for(i=0; i<MAX_NODES; i++){
					if(adjacencyMatrix[n.getIndex()][i] == 1){
						adj = nodeList.get(i);
						
						if(!adj.isVisited()){
							System.out.println("Node "+i);
							adj.setVisited(true);
							bfsQueue.add(adj);
						}
					}
				}
			}
		}
		
	}
	
	public void depthFirstSearch() {
		Stack<Node> stack = new Stack<Node>();
		
		Node first = nodeList.get(0);
		first.setVisited(true);
		stack.push(first);
		
		printNode(nodeList.indexOf(first));
		
		while(!stack.isEmpty()) {
			Node top = stack.peek();
			top.setVisited(true);
			printNode(nodeList.indexOf(top));
			
			for(int i = 0; i < MAX_NODES; i++) {
				if(adjacencyMatrix[top.getIndex()][i] == 1) {
					stack.push(nodeList.get(i));
				}
			}
		}
	}
	
	public void clearVisitedNodes(){
		
		Iterator<Node> i;
		
		i = nodeList.iterator();
		while(i.hasNext()){
			Node temp = i.next();
			temp.setVisited(false);
		}
	}
	
	public Node getFirstUnvisited(){
		
		Iterator<Node> i;
		Node firstUnvisited;
		
		i = nodeList.iterator();
		firstUnvisited = null;
		
		while(i.hasNext() && firstUnvisited==null){
			Node temp = i.next();
			
			if(!temp.isVisited())
				firstUnvisited = temp;
		}
		
		return firstUnvisited;
	}
}
