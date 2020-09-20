package oodp_hw1;

public class Main {
	public static void main(String[] args) {
		HotelService singleBed = new SingleBed();
		HotelService queenBed = new QueenBed();
		HotelService kingBed = new KingBed();
		
		singleBed.setNext(queenBed);
		queenBed.setNext(kingBed);
		kingBed.setNext(singleBed);
		
		System.out.println("One king bed room is requested");
		singleBed.process(new ClientRequest("king"));
		System.out.println("One single bed room is requested");
		singleBed.process(new ClientRequest("single"));
		System.out.println("One queen bed room is requested");
		singleBed.process(new ClientRequest("queen"));
		System.out.println("One king bed room is requested");
		singleBed.process(new ClientRequest("king"));
	}
}
