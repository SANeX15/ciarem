package ciarem.ctrl;

import ciarem.view.View_Dashboard;
import ciarem.dao.DAO_Customer;
import ciarem.view.View_new_Customer;


public class Ctrl_Dashboard {
	View_Dashboard view;
	
	public Ctrl_Dashboard(View_Dashboard view) {
		this.view = view;
		
		initCtrl();
	}
	
	private void initCtrl() {
		view.getCardCustomer().getBtnAddCustomers().addActionListener(e -> openAddCustomer());;
		view.getBtnNavCustomers().addActionListener(e -> switchCard("CARD_CUSTOMERS"));
	}
	
	private void switchCard(String cardName) {
		view.getCardLayout().show(view.getMainPanel(), cardName);
	}
	
	private void openAddCustomer() {
		View_new_Customer vc = new View_new_Customer(view);
		DAO_Customer dao_c = new DAO_Customer();
		Ctrl_Customer cc = new Ctrl_Customer(dao_c, vc);
	}
}
