package oodp_hw1;

public abstract class HotelService implements RoomFrame{
	private HotelService next;
	protected int count = 0;
	
	public HotelService getNext() {
		return this.next;
	}
	
	public void setNext(HotelService next) {
		this.next = next;
	}
	
	public void process(ClientRequest request) {
		if(isBedTypeMatch(request)) {
			count++;
			if(solve(request)) {	
				count = 0;
				System.out.println("** Room Service Provided **");
				wifiService();
				bathRoomService();
				diningRoomService();
				parkingService();
				System.out.println();
			}else {
				this.next.process(request);
			}
		}else {
			System.out.println("Next room is being checked");
			this.next.process(request);
		}
	}
	
	protected boolean isAvailable() {
		// 3/4 percetage
		int rand = (int)(Math.random()*4);
		return rand < 3;
	}
	
	public abstract boolean solve(ClientRequest request);
	protected abstract void wifiService();
	protected abstract void bathRoomService();
	protected abstract void diningRoomService();
	protected abstract void parkingService();
}
