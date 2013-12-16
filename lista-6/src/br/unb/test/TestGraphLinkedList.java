package br.unb.test;

import java.util.List;

import br.unb.graphLinkedList.Graph;
import br.unb.graphLinkedList.Node;


public class TestGraphLinkedList {

	public static void main(String[] args) {
		System.out.println("**Depth First Search**");
		dfsTest();
		
		System.out.println("\n**Breadth First Search**");
		bfsTest();
		
		System.out.println("\n**Topological Sort 1**");
		topologicalSortTest1();
		
		System.out.println("\n**Topological Sort 2**");
		topologicalSortTest2();
		
		System.out.println("\n**Topological Sort 3**");
		topologicalSortTest3();
		
		System.out.println("\n**Dijkstra**");
		dijkstraTest();
		
		System.out.println("\n**Dijkstra 2**");
		dijkstraTest2();
	}
	
	
	public static void dfsTest(){
		Graph graph = new Graph();
		
		Node n1 = new Node("Nó 1");
		Node n2 = new Node("Nó 2");
		Node n3 = new Node("Nó 3");
		Node n4 = new Node("Nó 4");
		Node n5 = new Node("Nó 5");
		Node n6 = new Node("Nó 6");
		Node n7 = new Node("Nó 7");
		
		graph.addNode(n1);
		graph.addNode(n2);
		graph.addNode(n3);
		graph.addNode(n4);
		graph.addNode(n5);
		graph.addNode(n6);
		graph.addNode(n7);
		
		graph.addEdge(n1.getIndex(), n4.getIndex(), 10);
		graph.addEdge(n1.getIndex(), n2.getIndex(), 10);
		graph.addEdge(n1.getIndex(), n5.getIndex(), 10);
		graph.addEdge(n4.getIndex(), n1.getIndex(), 10);
		graph.addEdge(n2.getIndex(), n1.getIndex(), 10);
		graph.addEdge(n5.getIndex(), n1.getIndex(), 10);
		
		graph.addEdge(n4.getIndex(), n5.getIndex(), 10);
		graph.addEdge(n4.getIndex(), n2.getIndex(), 10);
		graph.addEdge(n5.getIndex(), n4.getIndex(), 10);
		graph.addEdge(n2.getIndex(), n4.getIndex(), 10);
		
		graph.addEdge(n2.getIndex(), n6.getIndex(), 10);
		graph.addEdge(n6.getIndex(), n2.getIndex(), 10);
		
		graph.addEdge(n3.getIndex(), n7.getIndex(), 10);
		graph.addEdge(n7.getIndex(), n3.getIndex(), 10);
		
		graph.depthFirstSearch();
	}
	
	public static void bfsTest(){
		Graph graph = new Graph();
		
		Node n1 = new Node("Nó 1");
		Node n2 = new Node("Nó 2");
		Node n3 = new Node("Nó 3");
		Node n4 = new Node("Nó 4");
		Node n5 = new Node("Nó 5");
		Node n6 = new Node("Nó 6");
		Node n7 = new Node("Nó 7");
		
		graph.addNode(n1);
		graph.addNode(n2);
		graph.addNode(n3);
		graph.addNode(n4);
		graph.addNode(n5);
		graph.addNode(n6);
		graph.addNode(n7);
		
		graph.addEdge(n1.getIndex(), n5.getIndex(), 10);
		graph.addEdge(n1.getIndex(), n4.getIndex(), 10);
		graph.addEdge(n1.getIndex(), n2.getIndex(), 10);
		graph.addEdge(n5.getIndex(), n1.getIndex(), 10);
		graph.addEdge(n4.getIndex(), n1.getIndex(), 10);
		graph.addEdge(n2.getIndex(), n1.getIndex(), 10);
		
		graph.addEdge(n4.getIndex(), n5.getIndex(), 10);
		graph.addEdge(n4.getIndex(), n2.getIndex(), 10);
		graph.addEdge(n5.getIndex(), n4.getIndex(), 10);
		graph.addEdge(n2.getIndex(), n4.getIndex(), 10);
		
		graph.addEdge(n2.getIndex(), n6.getIndex(), 10);
		graph.addEdge(n6.getIndex(), n2.getIndex(), 10);
		
		graph.addEdge(n3.getIndex(), n7.getIndex(), 10);
		graph.addEdge(n7.getIndex(), n3.getIndex(), 10);
		
		graph.breadthFirstSearch();
	}
	
	public static void topologicalSortTest1(){
		Graph graph = new Graph();
		
		Node v1 = new Node("v1");
		Node v2 = new Node("v2");
		Node v3 = new Node("v3");
		Node v4 = new Node("v4");
		Node v5 = new Node("v5");
		Node v6 = new Node("v6");
		Node v7 = new Node("v7");
		
		graph.addNode(v1);
		graph.addNode(v2);
		graph.addNode(v3);
		graph.addNode(v4);
		graph.addNode(v5);
		graph.addNode(v6);
		graph.addNode(v7);
		
		
		graph.addEdge(v1.getIndex(), v4.getIndex(), 10);
		graph.addEdge(v1.getIndex(), v5.getIndex(), 10);
		graph.addEdge(v1.getIndex(), v7.getIndex(), 10);
		graph.addEdge(v2.getIndex(), v3.getIndex(), 10);
		graph.addEdge(v2.getIndex(), v5.getIndex(), 10);
		graph.addEdge(v2.getIndex(), v6.getIndex(), 10);
		graph.addEdge(v3.getIndex(), v5.getIndex(), 10);
		graph.addEdge(v3.getIndex(), v4.getIndex(), 10);
		graph.addEdge(v4.getIndex(), v5.getIndex(), 10);
		graph.addEdge(v5.getIndex(), v6.getIndex(), 10);
		graph.addEdge(v5.getIndex(), v7.getIndex(), 10);
		graph.addEdge(v6.getIndex(), v7.getIndex(), 10);
		
		List<Node> topologicalList =  graph.topologicalSort();
		
		for(Node n : topologicalList) {
			System.out.print(n.getLabel() +", ");
		}
	}
	
	public static void topologicalSortTest2(){
		Graph graph = new Graph();
		
		Node v2 = new Node("v2");
		Node v3 = new Node("v3");
		Node v4 = new Node("v4");
		Node v5 = new Node("v5");
		Node v6 = new Node("v6");
		
		graph.addNode(v2);
		graph.addNode(v3);
		graph.addNode(v4);
		graph.addNode(v5);
		graph.addNode(v6);
		
		graph.addEdge(v6.getIndex(), v2.getIndex(), 10);
		graph.addEdge(v2.getIndex(), v5.getIndex(), 10);
		graph.addEdge(v2.getIndex(), v3.getIndex(), 10);
		graph.addEdge(v5.getIndex(), v4.getIndex(), 10);
		graph.addEdge(v3.getIndex(), v4.getIndex(), 10);
		
		List<Node> topologicalList =  graph.topologicalSort();
		
		for(Node n : topologicalList) {
			System.out.print(n.getLabel() +", ");
		}
	}
	
	public static void topologicalSortTest3(){
		Graph graph = new Graph();
		
		Node v2 = new Node("v2");
		Node v3 = new Node("v3");
		Node v4 = new Node("v4");
		Node v5 = new Node("v5");
		Node v6 = new Node("v6");
		
		graph.addNode(v2);
		graph.addNode(v3);
		graph.addNode(v4);
		graph.addNode(v5);
		graph.addNode(v6);
		
		graph.addEdge(v6.getIndex(), v2.getIndex(), 10);
		graph.addEdge(v2.getIndex(), v5.getIndex(), 10);
		graph.addEdge(v2.getIndex(), v3.getIndex(), 10);
		graph.addEdge(v5.getIndex(), v4.getIndex(), 10);
		graph.addEdge(v3.getIndex(), v4.getIndex(), 10);
		graph.addEdge(v4.getIndex(), v6.getIndex(), 10);
		
		List<Node> topologicalList =  graph.topologicalSort();
		
		for(Node n : topologicalList) {
			System.out.print(n.getLabel() +", ");
		}
	}
	
	public static void dijkstraTest(){
		
		Graph graph = new Graph();
		
		Node nS = new Node("Source");
		Node n2 = new Node("N2");
		Node n6 = new Node("N6");
		Node n7 = new Node("N7");
		Node n5 = new Node("N5");
		Node n3 = new Node("N3");
		Node n4 = new Node("N4");
		Node nT = new Node("Target");
		
		graph.addNode(nS);
		graph.addNode(n2);
		graph.addNode(n6);
		graph.addNode(n7);
		graph.addNode(n5);
		graph.addNode(n3);
		graph.addNode(n4);
		graph.addNode(nT);
		
		graph.addEdge(nS.getIndex(), n2.getIndex(), 9);
		graph.addEdge(nS.getIndex(), n6.getIndex(), 14);
		graph.addEdge(nS.getIndex(), n7.getIndex(), 15);
		
		graph.addEdge(n2.getIndex(), n3.getIndex(), 23);
		
		graph.addEdge(n6.getIndex(), n3.getIndex(), 18);
		graph.addEdge(n6.getIndex(), n5.getIndex(), 30);
		graph.addEdge(n6.getIndex(), n7.getIndex(), 5);
		
		graph.addEdge(n7.getIndex(), n5.getIndex(), 20);
		graph.addEdge(n7.getIndex(), nT.getIndex(), 44);
		
		graph.addEdge(n5.getIndex(), n4.getIndex(), 11);
		graph.addEdge(n5.getIndex(), nT.getIndex(), 16);
		
		graph.addEdge(n3.getIndex(), n5.getIndex(), 2);
		graph.addEdge(n3.getIndex(), nT.getIndex(), 19);
		
		graph.addEdge(n4.getIndex(), n3.getIndex(), 6);
		graph.addEdge(n4.getIndex(), nT.getIndex(), 6);
		
		List<Node> shortestPath =  graph.getShortestPath(nS, nT);
		
		for(Node n : shortestPath) {
			System.out.println("\n" +n);
			System.out.println("Distance from source "+n.getDistanceFromSource());
		}
	}
	
	public static void dijkstraTest2(){
		
		Graph graph = new Graph();
		
		Node nA = new Node("NA");
		Node nB = new Node("NB");
		Node nC = new Node("NC");
		Node nD = new Node("ND");
		Node nE = new Node("NE");
		Node nF = new Node("NF");
		Node nG = new Node("NG");
		Node nH = new Node("NH");
		
		graph.addNode(nA);
		graph.addNode(nB);
		graph.addNode(nC);
		graph.addNode(nD);
		graph.addNode(nE);
		graph.addNode(nF);
		graph.addNode(nG);
		graph.addNode(nH);
		
		graph.addEdge(nA.getIndex(), nB.getIndex(), 3);
		graph.addEdge(nA.getIndex(), nC.getIndex(), 1);
		
		graph.addEdge(nB.getIndex(), nA.getIndex(), 3);
		graph.addEdge(nB.getIndex(), nD.getIndex(), 1);
		graph.addEdge(nB.getIndex(), nG.getIndex(), 5);
		
		graph.addEdge(nC.getIndex(), nA.getIndex(), 1);
		graph.addEdge(nC.getIndex(), nD.getIndex(), 2);
		graph.addEdge(nC.getIndex(), nF.getIndex(), 5);
		
		graph.addEdge(nD.getIndex(), nC.getIndex(), 2);
		graph.addEdge(nD.getIndex(), nF.getIndex(), 2);
		graph.addEdge(nD.getIndex(), nB.getIndex(), 1);
		graph.addEdge(nD.getIndex(), nE.getIndex(), 4);
		
		graph.addEdge(nE.getIndex(), nD.getIndex(), 4);
		graph.addEdge(nE.getIndex(), nG.getIndex(), 2);
		graph.addEdge(nE.getIndex(), nH.getIndex(), 1);
		
		graph.addEdge(nF.getIndex(), nC.getIndex(), 5);
		graph.addEdge(nF.getIndex(), nD.getIndex(), 2);
		graph.addEdge(nF.getIndex(), nH.getIndex(), 3);
		
		graph.addEdge(nG.getIndex(), nB.getIndex(), 5);
		graph.addEdge(nG.getIndex(), nE.getIndex(), 2);
		
		graph.addEdge(nH.getIndex(), nF.getIndex(), 3);
		graph.addEdge(nH.getIndex(), nE.getIndex(), 1);
		
		List<Node> shortestPath =  graph.getShortestPath(nA, nH);
		
		for(Node n : shortestPath) {
			System.out.println("\n" +n);
			System.out.println("Distance from source "+n.getDistanceFromSource());
		}
	}
}
