package ciarem.view.cards;

import javax.swing.*;
import javax.swing.table.*;

import com.formdev.flatlaf.extras.FlatSVGIcon;

//import ciarem.ctrl.Ctrl_Customer;
//import ciarem.dao.DAO_Customer;
//import ciarem.view.View_Customer;

import java.awt.*;

public class Card_Customer extends JPanel {
	private static final long serialVersionUID = 1L;
	private JPanel top;
	public JButton Btn_addC, Btn_updC, Btn_delC;
	FlatSVGIcon iconAdd, iconEdit, iconDelete;
	DefaultTableModel defTableModel;
	JTable Tbl_Customer;
	
	public Card_Customer() {
		setLayout(new BorderLayout());
		top = new JPanel();
		iconAdd  = new FlatSVGIcon("ciarem/icons/add.svg", 18, 18);
		iconEdit  = new FlatSVGIcon("ciarem/icons/edit.svg", 18, 18);
		iconDelete  = new FlatSVGIcon("ciarem/icons/delete.svg", 18, 18);
		Btn_addC = new JButton("Add", iconAdd);
		Btn_updC = new JButton("Edit", iconEdit);
		Btn_delC = new JButton("Delete", iconDelete);
		
		String[] Headers = {
				"Aadhar No.",
				"Full Name",
				"Mobile Number",
				"Date of Birth"
		};
		
		top.add(Btn_addC);
		top.add(Btn_updC);
		top.add(Btn_delC);
		
		defTableModel = new DefaultTableModel(Headers, 0) {
			@Override
			public boolean isCellEditable(int row, int column) { return false; }
		};
		Tbl_Customer = new JTable(defTableModel);
		
		add(top, BorderLayout.NORTH);
		add(new JScrollPane(Tbl_Customer), BorderLayout.CENTER);
	}

	public JButton getBtnAddCustomer() { return Btn_addC; }
	public JButton getBtnEditCustomer() { return Btn_updC; }
	public JButton getBtnDeleteCustomer() { return Btn_delC; }
    public JTable getTable() { return Tbl_Customer; }
    public DefaultTableModel getTableModel() { return defTableModel; }
}
