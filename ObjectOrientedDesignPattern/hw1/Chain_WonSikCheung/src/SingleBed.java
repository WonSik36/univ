package oodp_hw1;

public class SingleBed extends HotelService {
	private static String bedType = "single";
	
	public SingleBed() {
		System.out.println("Single Bed Object Created");
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
			System.out.println("Single Bed Room is available now. One Single Bed reserved");
			return true;
		}else {
			System.out.println("Checking a Single Bed Room: "+count+" time");
			System.out.println("Single Bed Room is not available");
			return false;
		}
	}

	@Override
	public boolean isBedTypeMatch(ClientRequest request) {
		return bedType.equals(request.getBedType());
	}

	@Override
	protected void wifiService() {
		System.out.println("WIFI : 1 Giga per one night ready");
	}
	
	@Override
	protected void bathRoomService() {
		System.out.println("2 face towel , 1 shower gown , 1 cosmetic available");
	}
	
	@Override
	protected void diningRoomService() {
		System.out.println("breakfast buffet for $10");
	}
	
	@Override
	protected void parkingService() {
		System.out.println("parking spaces for one car available");
	}
}
