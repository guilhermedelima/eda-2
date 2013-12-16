package br.unb.graph;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;

/*
 * Classe que representa o Grafo direcionado
 * Grafo é composto por uma lista de nós. Cada nó possui uma lista de adjacência.
 */
public class Graph {

	private List<Node> nodeList;
	private static final int MAX_NODES = 100;
	
	public Graph(){
		this.nodeList = new ArrayList<Node>(MAX_NODES);
	}
	
	/* Método para adicionar nó no Grafo */
	public void addNode(Node node){
		int size;
		size = nodeList.size();
		
		if(size < MAX_NODES){
			node.setIndex(size);
			nodeList.add(node);
		}else{
			System.out.println("The graph is full. Max of allowed nodes is '"+ MAX_NODES +"'");
		}
	}
	
	/* Método para criar arestas entre dois nós */
	public void addEdge(int aIndex, int bIndex, int cost){
		List<Edge> adjacencyList;
		Node n;
		
		n = nodeList.get(aIndex);
		adjacencyList = n.getAdjacencyList();
		
		Edge e = new Edge(bIndex, cost);
		adjacencyList.add(e);
	}
	
	/* Método que realiza a busca em largura no Grafo */
	public void breadthFirstSearch(){
		
		Queue<Node> bfsQueue;
		Node first, n, adj;
		
		bfsQueue = new LinkedList<Node>();
		
		while( (first=getFirstUnvisitedNode()) != null ){
			bfsQueue.add(first);
			first.setVistited(true);
			
			while(!bfsQueue.isEmpty()){
				n = bfsQueue.remove();
				
				while( (adj = getFirstUnvisitedNeighbor(n)) != null){
					printEdge(n, adj);
					adj.setVistited(true);
					bfsQueue.add(adj);
				}
			}
		}
		
		clearVisitedNodes();
	}
	
	/* Método que realiza a busca em profundidade no Grafo */
	public void depthFirstSearch(){
		
		Node n;
		
		while( (n=getFirstUnvisitedNode()) != null){
			dfsVisit(n);
		}
		
		clearVisitedNodes();
	}
	
	/* Chamada recursiva utilizada pela busca em profundidade */
	private void dfsVisit(Node n){
		
		Node adj;
		n.setVistited(true);
		
		while( (adj=getFirstUnvisitedNeighbor(n)) != null){
			printEdge(n, adj);
			dfsVisit(adj);
		}
	}
	
	/* Método que realiza ordenção topológica do Grafo */
	public List<Node> topologicalSort(){
		
		int count[];
		int smallerDegree, smallerIndex;
		Node minimumDegreeNode;
		List<Node> topologicalOrder;
		
		//Preenche o vetor Count (Grau de cada Nó)
		count = bfsNodesFillCount();
		topologicalOrder = new ArrayList<Node>();
		
		for(int i=0; i<nodeList.size(); i++){
			
			smallerIndex = -1;
			smallerDegree= Integer.MAX_VALUE;
			minimumDegreeNode = null;
		
			//Verifica Nó com menor Grau
			for(int j=0; j<count.length; j++){
				
				if(count[j] < smallerDegree){
					smallerDegree = count[j];
					smallerIndex = j;
				}
			}
			
			//Retorna lista vazia caso o Grafo não possua Ordenação topológica
			if(smallerDegree > 0){
				System.out.println("Graph is not a DAG");
				return new ArrayList<Node>();
			}
			
			//Adiciona nó com menor Grau na ordenação topológica
			minimumDegreeNode = nodeList.get(smallerIndex);
			topologicalOrder.add(minimumDegreeNode);
			
			//"Remove" nó do grafo (Passa a ignorar o nó encontrado)
			count[smallerIndex] = Integer.MAX_VALUE;
			
			//Atualiza os vizinhos do nó no vetor count
			for(Edge e : minimumDegreeNode.getAdjacencyList()){
				count[e.getNodeIndex()]--;
			}
		
		}
		
		return topologicalOrder;
	}
	
	/* Busca por largura para preencher vetor count, utilizado na Ordenação Topológica */
	private int[] bfsNodesFillCount(){
		
		Queue<Node> bfsQueue;
		List<Node> neighbors;
		Node first, n;
		int count[];
		
		bfsQueue = new LinkedList<Node>();
		count = new int[nodeList.size()];
		
		while( (first=getFirstUnvisitedNode()) != null ){
			bfsQueue.add(first);
			first.setVistited(true);
			
			while(!bfsQueue.isEmpty()){
				n = bfsQueue.remove();
				
				neighbors = getNeighbors(n);
				
				for(Node adj : neighbors){
				
					count[adj.getIndex()]++;
					
					if(!adj.isVistited()){
						adj.setVistited(true);
						bfsQueue.add(adj);
					}
				}
			}
		}
		
		clearVisitedNodes();	
		return count;
	}
	
	/* 
	 * Algoritmo de Dijkstra para encontrar menor caminho entre dois nós 
	 * Retorna uma lista de nós que representa o menor caminho, partindo do alvo até a fonte
	 * Se não houver caminho entre os nós é retornado uma Lista vazia
	 */
	public List<Node> getShortestPath(Node source, Node target){
		
		//Limpa os valores dos nós para uma nova busca
		clearVisitedNodes();
		
		List<Node> shortestPath;
		Node temp;
		temp = target;
		
		//Calcula menor caminho dos nós do grafo até a fonte
		calculateShortestPaths(source);
		shortestPath = new ArrayList<Node>();
		
		//Percorre o alvo até a fonte, caso exista caminho entre os nós
		while(temp != null){
			shortestPath.add(temp);
			temp = temp.getPrev();
		}
		
		return shortestPath;
	}
	
	/* 
	 * Método que calcula o menor caminho definitivo de todos os nós até a fonte
	 * Utiliza Fila de prioridades para que seja possível adicionar os nós a serem visitados
	 * de forma ordenada (Menor caminho -> Maior Prioridade). 
	 */
	private void calculateShortestPaths(Node source){

		PriorityQueue<Node> queueNodes;
		Node node, adj;
		int currentCost;
		
		//Fila de prioridade dos nós a serem visitados
		queueNodes = new PriorityQueue<Node>();
		
		source.setDistanceFromSource(0);
		queueNodes.add(source);
		
		//Executa enquanto houver nós a serem visitados
		while(!queueNodes.isEmpty()){
			
			//Visita um nó com menor caminho já definitivo
			node = queueNodes.remove();
			node.setVistited(true);
			
			//Calcula o menor caminho para os vizinhos não visitados
			for(Edge e : node.getAdjacencyList()){
				adj = nodeList.get(e.getNodeIndex());
				
				if(!adj.isVistited()){
					
					currentCost = node.getDistanceFromSource() + e.getCost();

					//Atualiza menor caminho de um nó
					if(currentCost < adj.getDistanceFromSource()){
						
						queueNodes.remove(adj);
						
						adj.setDistanceFromSource(currentCost);
						adj.setPrev(node);
						
						queueNodes.add(adj);
					}
				}
			}
		}

	}
	
	/* Método para "limpar" os nós após a utilização de alguma busca */
	private void clearVisitedNodes(){
		for(Node n : nodeList){
			n.setVistited(false);
			n.setPrev(null);
			n.setDistanceFromSource(Integer.MAX_VALUE);
		}
	}
	
	/* Método para retornar um nó não visitado no grafo */
	private Node getFirstUnvisitedNode(){
		Node unvisited = null;
		
		for(Node n : nodeList){
			if(!n.isVistited()){
				unvisited = n;
				break;
			}
		}
		
		return unvisited;
	}
	
	/* Método para retornar todos os vizinhos de um nó */
	private List<Node> getNeighbors(Node node){
		
		List<Node> neighbors;
		Node neighbor;
		int neighborIndex;
		
		neighbors = new ArrayList<Node>();
		
		for(Edge e : node.getAdjacencyList()){
			neighborIndex = e.getNodeIndex();
			neighbor = nodeList.get(neighborIndex);
			
			neighbors.add(neighbor);
		}
		
		return neighbors;
	}
	
	/* Método para retornar um vizinho ainda não visitado */
	private Node getFirstUnvisitedNeighbor(Node node){
		
		int neighborIndex;
		Node neighbor, tempNode;
		
		neighbor = null;
		
		for(Edge e : node.getAdjacencyList()){
			neighborIndex = e.getNodeIndex();
			tempNode = nodeList.get(neighborIndex);
			
			if(!tempNode.isVistited()){
				neighbor = tempNode;
				break;
			}
		}
		
		return neighbor;
	}
	
	/* Impressão das arestas marcadas durante as buscas */
	private void printEdge(Node a, Node b) {
		System.out.println("Edge between "+ a +" and "+ b);
	}
	
}
