package ciarem.ctrl;

import ciarem.view.View_Dashboard;

import java.time.LocalDate;

import javax.swing.JOptionPane;
import javax.swing.JTable;

import ciarem.dao.DAO_Customer;
import ciarem.mdl.Mdl_Customer;
import ciarem.view.View_new_Customer;


public class Ctrl_Dashboard {
	View_new_Customer vc;
	View_Dashboard view;
	Ctrl_Customer cc;
	DAO_Customer dao_c;
	
	public Ctrl_Dashboard(View_Dashboard view) {
		this.view = view;
		
		initCtrl();
	}
	
	private void initCtrl() {
		view.getCardCustomer().getBtnAddCustomer().addActionListener(e -> openAddCustomer());
		view.getCardCustomer().getBtnEditCustomer().addActionListener(e -> openEditCustomer());
		view.getCardCustomer().getBtnDeleteCustomer().addActionListener(e -> deleteCustomer());
		view.getBtnNavCustomers().addActionListener(e -> switchCard("CARD_CUSTOMERS"));
		
		dao_c = new DAO_Customer();
		vc = new View_new_Customer(view);
		cc = new Ctrl_Customer(dao_c, vc);

		loadData(1);
	}
	
	private void loadData(int card) {
		switch(card) {
			case 1:
				view.getCardCustomer().getTableModel().setRowCount(0);
				
				for(Mdl_Customer c : dao_c.read()) {
					Object[] row = {
							c.getID(),
							c.getName(),
							c.getPhone(),
							c.getDob()
					};
					view.getCardCustomer().getTableModel().addRow(row);
				}
		}
	}
	
	private void switchCard(String cardName) {
		view.getCardLayout().show(view.getMainPanel(), cardName);
	}
	
	private void openAddCustomer() {
		vc = new View_new_Customer(view);
		cc = new Ctrl_Customer(dao_c, vc);
		vc.setVisible(true);
		loadData(1);
	}
	private void openEditCustomer() {
		JTable tbl = view.getCardCustomer().getTable();
		int selectedRow = tbl.getSelectedRow();
		
		if (selectedRow == -1) {
	        JOptionPane.showMessageDialog(view, "Please select a customer from the table to edit.", "No Selection", JOptionPane.WARNING_MESSAGE);
	        return;
	    }
		
		String id = tbl.getValueAt(selectedRow, 0).toString();
		String name = tbl.getValueAt(selectedRow, 1).toString();
		String phone = tbl.getValueAt(selectedRow, 2).toString();
		String dobStr = tbl.getValueAt(selectedRow, 3).toString();
		
		vc = new View_new_Customer(view, id, name, phone, LocalDate.parse(dobStr));
		cc = new Ctrl_Customer(dao_c, vc);
		
		vc.setVisible(true);
		loadData(1);
	}
	private void deleteCustomer() {
	    JTable tbl = view.getCardCustomer().getTable();
	    int selectedRow = tbl.getSelectedRow();
	    
	    if (selectedRow == -1) {
	        JOptionPane.showMessageDialog(view, "Please select a customer from the table to delete.", "No Selection", JOptionPane.WARNING_MESSAGE);
	        return;
	    }
	    
	    String id = tbl.getValueAt(selectedRow, 0).toString();
	    String name = tbl.getValueAt(selectedRow, 1).toString();
	    
	    int choice = JOptionPane.showConfirmDialog(view, 
	        "Are you sure you want to permanently delete " + name + "?", 
	        "Confirm Deletion", 
	        JOptionPane.YES_NO_OPTION, 
	        JOptionPane.WARNING_MESSAGE);
	        
	    if (choice == JOptionPane.YES_OPTION) {
	        if (dao_c.delete(id)) {
	            loadData(1);
	        } else {
	            JOptionPane.showMessageDialog(view, "Failed to delete customer.", "Database Error", JOptionPane.ERROR_MESSAGE);
	        }
	    }
	}
}
