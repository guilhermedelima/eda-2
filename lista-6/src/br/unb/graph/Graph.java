package br.unb.graph;

import java.util.ArrayList;
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
	
	public int getNumberOfNodes(){
		return nodeList.size();
	}
	
	public void addNode(Node node){
		if(nodeList.size() <= MAX_NODES) {
			node.setIndex(nodeList.size());
			nodeList.add(node);
		} else {
			System.out.println("The graph is full. Max of allowed nodes is '"+ MAX_NODES +"'");
		}
	}
	
	public void addEdge(int aIndex, int bIndex) {
		if (aIndex != bIndex) {
			adjacencyMatrix[aIndex][bIndex] = 1;
		} else {
			System.out.println("A node cant have an edge to itself (same indexes '"+ aIndex +"' were passed)");
		}
	}
	
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
				
				for(i=0; i < getNumberOfNodes(); i++){
					if(adjacencyMatrix[n.getIndex()][i] == 1){
						adj = nodeList.get(i);
						
						if(!adj.isVisited()){
							printEdge(n, adj);
							adj.setVisited(true);
							bfsQueue.add(adj);
						}
					}
				}
			}
		}

		clearAllNodeVisits();
	}
	
	public void depthFirstSearch() {
		Stack<Node> stack = new Stack<Node>();
		Node first, top, adj;
		
		while( (first = getFirstUnvisited()) != null ){
			stack.push(first);
			
			while(!stack.isEmpty()) {
				top = stack.peek();
				top.setVisited(true);
				
				boolean foundNode = false;
				
				for(int i = 0; i < getNumberOfNodes(); i++) {
					if(adjacencyMatrix[top.getIndex()][i] == 1) {						
						adj = nodeList.get(i);
						if (!adj.isVisited()) {
							printEdge(top, adj);
							stack.push(adj);
							foundNode = true;
							break;
						}
					}
				}
				if(!foundNode)
					stack.pop();
			}
		}
		
		clearAllNodeVisits();
	}
	
	private void printEdge(Node a, Node b) {
		System.out.println("Edge between "+ a +" and "+ b);
	}
	
	private Node getFirstUnvisited(){    
        Node firstUnvisited = null;
        
        for (Node node : nodeList) {
        	if(!node.isVisited()) {
        		firstUnvisited = node;
        		break;
        	}
        }
        
        return firstUnvisited;
	}
	
	private void clearAllNodeVisits() {
		for (Node node : nodeList) 
			node.setVisited(false);
	}
}
