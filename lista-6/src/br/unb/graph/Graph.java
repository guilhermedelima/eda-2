package br.unb.graph;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;

public class Graph {
	
	private List<Node> nodeList;
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
	
	public List<Node> topologicalSort() {
		List<Node> topologicalList = new ArrayList<Node>();
		Graph clone = this.clone();
		List<Integer> nodeDegreeList = dfsNodesDegree(clone);
		
		for(int i = 0; i < getNumberOfNodes(); i++) {
			int minimumDegree = Integer.MAX_VALUE;
			int nodeDegree;
			Node minimumDegreeNode = null;
			
			for(int j = 0; j < getNumberOfNodes(); j++) {
				nodeDegree = nodeDegreeList.get(j);
				
				if(nodeDegree < minimumDegree) {
					minimumDegree = nodeDegree;
					minimumDegreeNode = nodeList.get(j);
				}
			}
			
			if(minimumDegree > 0) {
				System.out.println("Graph is not a DAG");
				return null;
			}
			
			topologicalList.add(minimumDegreeNode);
			clone.removeNode(minimumDegreeNode);
			nodeDegreeList.get(minimumDegreeNode.getIndex());
		}
		
		return topologicalList;
	}
	
	private void removeNode(Node node) {
		nodeList.remove(node.getIndex());
		for(int i = 0; i < getNumberOfNodes(); i++) {
			adjacencyMatrix[node.getIndex()][i] = 0;
			adjacencyMatrix[i][node.getIndex()] = 0;
		}
	}

	public Graph clone() {
		Graph clone = new Graph();
		
		clone.adjacencyMatrix = this.adjacencyMatrix;
		clone.nodeList = this.nodeList;
		
		return clone;
	}
	
	private List<Integer> dfsNodesDegree(Graph clone) {
		Stack<Node> stack = new Stack<Node>();
		Node first, top, adj;
		List<Integer> nodeDegreeList = new ArrayList<Integer>();
		for(int i = 0; i < getNumberOfNodes(); i++) {
			nodeDegreeList.add(0);
		}
		
		while( (first = clone.getFirstUnvisited()) != null ){
			stack.push(first);
			
			while(!stack.isEmpty()) {
				top = stack.peek();
				top.setVisited(true);
				
				boolean foundNode = false;
				
				for(int i = 0; i < clone.getNumberOfNodes(); i++) {
					if(clone.adjacencyMatrix[top.getIndex()][i] == 1) {						
						adj = clone.nodeList.get(i);
						if (!adj.isVisited()) {
							Integer nodeDegree = nodeDegreeList.get(top.getIndex());
							nodeDegree++;
							
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
		
		return nodeDegreeList;
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
