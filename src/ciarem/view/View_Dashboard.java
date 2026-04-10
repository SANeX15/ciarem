package ciarem.view;

import javax.swing.*;

import ciarem.ctrl.Ctrl_Customer;
import ciarem.dao.DAO_Customer;
import ciarem.view.cards.Card_Customer;

import java.awt.*;

public class View_Dashboard extends JFrame {
	private static final long serialVersionUID = 1L;
	private CardLayout cL;
	private JPanel Pnl_main, Pnl_nav, Crd_Customer;
	private JButton Btn_nav_c;
	
	public View_Dashboard() {
		setTitle("Dashboard");
		setSize(400,300);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
		setLayout(new BorderLayout());
		
		init();
		
		setVisible(true);
	}
	
	private void init() {
		cL = new CardLayout();
		Pnl_main = new JPanel(cL);
		Pnl_nav = new JPanel();
		Crd_Customer = new Card_Customer();
		
		Pnl_main.add(Crd_Customer, "CARD_CUSTOMERS");
		Pnl_nav.add(Btn_nav_c);
		
		add(Pnl_main, BorderLayout.CENTER);
		add(Pnl_nav, BorderLayout.NORTH);
	}
	
	public Card_Customer getCardCustomer() { return (Card_Customer)Crd_Customer;}
	public CardLayout getCardLayout() { return cL; }
    public JPanel getMainPanel() { return Pnl_main; }
    public JButton getBtnNavCustomers() { return Btn_nav_c; }
}
