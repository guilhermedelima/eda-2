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
	
	public int getListSize(){
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
			System.out.println("A node cant have an edge to itsfel (same indexes '"+ aIndex +"' were passed)");
		}
	}
	
	void printNode(int index){
		System.out.println("Node "+ nodeList.get(index).getLabel() +"["+ index +"]");
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
				
				for(i=0; i<MAX_NODES; i++){
					if(adjacencyMatrix[n.getIndex()][i] == 1){
						adj = nodeList.get(i);
						
						if(!adj.isVisited()){
							printNode(adj.getIndex());
							adj.setVisited(true);
							bfsQueue.add(adj);
						}
					}
				}
			}
		}

		unvistAllNodes();
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
				printNode(nodeList.indexOf(top));
				
				for(int i = 0; i < MAX_NODES; i++) {
					if(adjacencyMatrix[top.getIndex()][i] == 1 && !nodeList.get(i).isVisited()) {
						adj = nodeList.get(i);
						stack.push(adj);
						
						foundNode = true;
						break;
					}
				}
				if(!foundNode)
					stack.pop();
			}
		}
		
		unvistAllNodes();
	}
	
	public Node getFirstUnvisited(){    
        Node firstUnvisited = null;
        
        for (Node node : nodeList) {
        	if(!node.isVisited()) {
        		firstUnvisited = node;
        		break;
        	}
        }
        
        return firstUnvisited;
	}
	
	private void unvistAllNodes() {
		for (Node node : nodeList) 
			node.setVisited(false);
	}
}
