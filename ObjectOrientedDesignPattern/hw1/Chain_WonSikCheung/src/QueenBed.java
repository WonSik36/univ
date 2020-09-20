package oodp_hw1;

public class QueenBed extends HotelService {
	private static String bedType = "queen";
	
	public QueenBed() {
		System.out.println("Queen Bed Object Created");
	}

	@Override
	public boolean solve(ClientRequest request) {
		try {
			for(int i=0;i<5;i++) {
				Thread.sleep(500);
				System.out.print(".");
			}
		}catch(InterruptedException e) {}
		
		if(isAvailable()) {
			System.out.println("Queen Bed Room is available now. One Queen Bed reserved");
			return true;
		}else {
			System.out.println("Checking a Queen Bed Room: "+count+" time");
			System.out.println("Queen Bed Room is not available");
			return false;
		}
	}

	@Override
	public boolean isBedTypeMatch(ClientRequest request) {
		return bedType.equals(request.getBedType());
	}

	@Override
	protected void wifiService() {
		System.out.println("WIFI : 2 Giga per one night ready");
	}
	
	@Override
	protected void bathRoomService() {
		System.out.println("4 face towel , 2 shower gown , 1 cosmetic available");
	}
	
	@Override
	protected void diningRoomService() {
		System.out.println("1 free breakfast buffet service");
	}
	
	@Override
	protected void parkingService() {
		System.out.println("parking spaces for one car available");
	}
}
