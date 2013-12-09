package br.unb.graph;

public class Node {
	
	private String label;
	private boolean visited;
	private int index;
	
	public Node(String label, int index) {
		this.label = label;
		this.visited = false;
		this.index = index;
	}

	public String getLabel() {
		return label;
	}

	public void setLabel(String label) {
		this.label = label;
	}

	public boolean isVisited() {
		return visited;
	}

	public void setVisited(boolean visited) {
		this.visited = visited;
	}
	
	public int getIndex() {
		return index;
	}
}

