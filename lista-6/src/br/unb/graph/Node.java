package br.unb.graph;

public class Node {
	
	private String label;
	private boolean visited;
	private int index;
	
	public Node(String label) {
		this.label = label;
		this.visited = false;
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
	
	protected void setIndex(int index) {
		this.index =  index;
	}

	@Override
	public String toString() {
		return "\"" + label + "["+ index + "]\"";
	}
	
	
}

