package br.unb.graph;

import java.util.ArrayList;
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

		// Modify the DFS (BFS) to fill a vector count that stores, for each node v, the number of remaining edges that are incident in v
		List<Integer> nodeDegreeList = bfsNodesDegree(clone);
		
		for(int i = 0; i < getNumberOfNodes(); i++) {
			int minimumDegree = Integer.MAX_VALUE;
			int nodeDegree;
			Node minimumDegreeNode = null;
			
			for(int j = 0; j < clone.getNumberOfNodes(); j++) {
				nodeDegree = nodeDegreeList.get(j);
				
				if(nodeDegree < minimumDegree) {
					minimumDegree = nodeDegree;
					// node with minimum degree in G
					minimumDegreeNode = clone.nodeList.get(j);
				}
			}
			

			// If v has degree larger than 0 Return G is not a DAG
			if(minimumDegree > 0) {
				System.out.println("Graph is not a DAG");
				return new ArrayList<Node>();
			}
			
			List<Node> nodesTobeUpdatedList = new ArrayList<Node>();
			for(int j = 0; j < clone.getNumberOfNodes(); j++) {
				if(clone.adjacencyMatrix[minimumDegreeNode.getIndex()][j] == 1) {
					nodesTobeUpdatedList.add(clone.nodeList.get(j));
				}
			}
			// Add v to the topological order
			topologicalList.add(minimumDegreeNode);

			//Remove v from G
			clone.removeNode(minimumDegreeNode);
			nodeDegreeList.remove(minimumDegreeNode.getIndex());
			
			// Update the vector count for the nodes adjacent to v
			for(Node nodeTobeUpdated : nodesTobeUpdatedList) {
				int mustBeUpdatedNodeDegree = nodeDegreeList.get(nodeTobeUpdated.getIndex());
				nodeDegreeList.set(nodeTobeUpdated.getIndex(), mustBeUpdatedNodeDegree-1);
			}		
		}
		
		return topologicalList;
	}
	
	public void removeNode(Node toBeremoved) {
		for(int i = toBeremoved.getIndex(); i < getNumberOfNodes() && i < MAX_NODES-1; i++) {
			for(int j = 0; j < getNumberOfNodes(); j++) {
				adjacencyMatrix[i][j] = adjacencyMatrix[i+1][j];
			}
		}
		for(int i = toBeremoved.getIndex(); i < getNumberOfNodes() && i < MAX_NODES-1; i++) {
			for(int j = 0; j < getNumberOfNodes(); j++) {
				adjacencyMatrix[j][i] = adjacencyMatrix[j][i+1];
			}
		}
		for(int i = toBeremoved.getIndex()+1; i < getNumberOfNodes(); i++) {
			nodeList.get(i).setIndex(i-1);
		}
		nodeList.remove(toBeremoved);
	}

	public Graph clone() {
		Graph clone = new Graph();
		
		for(int i = 0; i < getNumberOfNodes(); i++) {
			for(int j = 0; j < getNumberOfNodes(); j++) {
				clone.adjacencyMatrix[i][j] = adjacencyMatrix[i][j];
			}
		}
		
		for(Node node : nodeList) {
			clone.addNode(new Node(node.getLabel()));
		}
		 
		return clone;
	}
	
	private List<Integer> bfsNodesDegree(Graph clone) {
		Queue<Node> bfsQueue;
		Node first, n, adj;
		List<Integer> nodeDegreeList = new ArrayList<Integer>();
		for(int i = 0; i < clone.getNumberOfNodes(); i++) {
			nodeDegreeList.add(0);
		}
		
		bfsQueue = new LinkedList<Node>();
		int i;
		while( (first = clone.getFirstUnvisited()) != null){
			bfsQueue.add(first);
			first.setVisited(true);
			
			while(!bfsQueue.isEmpty()){	
				n = bfsQueue.remove();
				
				for(i=0; i < clone.getNumberOfNodes(); i++){
					if(clone.adjacencyMatrix[n.getIndex()][i] == 1){
						adj = clone.nodeList.get(i);
						Integer nodeDegree = nodeDegreeList.get(adj.getIndex());
						nodeDegreeList.set(adj.getIndex(), nodeDegree + 1);
						if(!adj.isVisited()){
							adj.setVisited(true);
							bfsQueue.add(adj);
						}
					}
				}
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
