package br.unb.graph;

import java.util.LinkedList;
import java.util.List;

/*
 * Classe que representa um nó no grafo. Implementa Comparable para que
 * seja possível inserir elementos de forma ordenada na Fila de Prioridades
 * utilizada no algoritmo de Dijkstra
 */
public class Node implements Comparable<Node>{
	
	private List<Edge> adjacencyList;
	private int index;
	private String label;
	private boolean vistited;
	
	private int distanceFromSource;
	private Node prev;
	
	public Node(String label){
		this.label = label;
		this.vistited = false;
		this.adjacencyList = new LinkedList<Edge>();
		
		prev = null;
		distanceFromSource = Integer.MAX_VALUE;
	}
	
	public int getDistanceFromSource() {
		return distanceFromSource;
	}

	protected void setDistanceFromSource(int distanceFromSource) {
		this.distanceFromSource = distanceFromSource;
	}

	public Node getPrev() {
		return prev;
	}

	protected void setPrev(Node prev) {
		this.prev = prev;
	}

	public int getIndex() {
		return index;
	}

	protected void setIndex(int index) {
		this.index = index;
	}
	
	public List<Edge> getAdjacencyList() {
		return adjacencyList;
	}

	public String getLabel(){
		return label;
	}

	public boolean isVistited() {
		return vistited;
	}
	
	public void setVistited(boolean vistited) {
		this.vistited = vistited;
	}
	
	@Override
	public String toString() {
		return "Node "+label;
	}

	/* Método que realiza comparação das distancias de dois nós, para 
	 * inserir na fila de prioridades ordenadamente
	 */
	@Override
	public int compareTo(Node secondNode) {
		
		return Integer.compare(distanceFromSource, secondNode.distanceFromSource);
	}
	
}
