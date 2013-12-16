package br.unb.graphLinkedList;

/*
 * Classe que representa as arestas utilizadas na Lista de Adjacência
 */
public class Edge {
	
	private int cost;
	private int nodeIndex;

	public Edge(int nodeIndex, int cost){
		this.nodeIndex = nodeIndex;
		this.cost = cost;
	}

	public int getCost() {
		return cost;
	}

	public int getNodeIndex() {
		return nodeIndex;
	}	
	
}
