package ciarem.view.cards;

import javax.swing.*;
import javax.swing.table.*;

//import ciarem.ctrl.Ctrl_Customer;
//import ciarem.dao.DAO_Customer;
//import ciarem.view.View_Customer;

import java.awt.*;

public class Card_Customer extends JPanel {
	private static final long serialVersionUID = 1L;
	private JPanel top;
	public JButton Btn_addC;
	DefaultTableModel defTableModel;
	JTable Tbl_Customer;
	
	public Card_Customer() {
		setLayout(new BorderLayout());
		top = new JPanel();
		Btn_addC = new JButton("+");
		String[] Headers = {
				"Aadhar No.",
				"Full Name",
				"Mobile Number",
				"Date of Birth"
		};
		
		top.add(Btn_addC);
		
		defTableModel = new DefaultTableModel(Headers, 0) {
			@Override
			public boolean isCellEditable(int row, int column) { return false; }
		};
		Tbl_Customer = new JTable(defTableModel);
		
		add(top, BorderLayout.NORTH);
		add(new JScrollPane(Tbl_Customer), BorderLayout.CENTER);
	}

	public JButton getBtnAddCustomers() { return Btn_addC; }
    public DefaultTableModel getTableModel() { return defTableModel; }
}
