package ciarem.dao;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

import ciarem.mdl.Mdl_Customer;

public class DAO_Customer {

	public boolean create(Mdl_Customer cus) {
		String insertQuery = "INSERT INTO customers (id,NAME,PHONE,DOB) VALUES (?,?,?,?);";
		try(Connection conn = DBHelper.getConnection();
				PreparedStatement ps = conn.prepareStatement(insertQuery)){
			
			ps.setString(1, cus.getID());
			ps.setString(2, cus.getName());
			ps.setString(3, cus.getPhone());
			ps.setString(4, cus.getDob().toString());
			
			return ps.executeUpdate() > 0;
		}
		catch(Exception e) {
			return false;
		}
	}
	
	public List<Mdl_Customer> read(){
		String selectQuery = "SELECT * FROM customers;";
		List<Mdl_Customer> list = new ArrayList<>();
		
		try(Connection conn = DBHelper.getConnection();
				PreparedStatement ps = conn.prepareStatement(selectQuery);
				ResultSet rs = ps.executeQuery()){
			while (rs.next()) {
				Mdl_Customer c = new Mdl_Customer(
					rs.getString("id"),
					rs.getString("NAME"),
					rs.getString("PHONE"),
					LocalDate.parse(rs.getString("DOB"))
				);
				list.add(c);
			}
		}
		catch(Exception e) {
			System.out.println("Select Failed");
		}
		return list;
	}
	
	public boolean update(Mdl_Customer cus) {
		String updateQuery = "UPDATE customers SET NAME = ?, PHONE = ?, DOB = ? WHERE id = ?;";
		try(Connection conn = DBHelper.getConnection();
				PreparedStatement ps = conn.prepareStatement(updateQuery)){
			
			ps.setString(1, cus.getName());
			ps.setString(2, cus.getPhone());
			ps.setString(3, cus.getDob().toString());
			ps.setString(4, cus.getID());
			
			return ps.executeUpdate() > 0;
		}
		catch(Exception e) {
			return false;
		}
	}
	
	public boolean delete(String id) {
		String deleteQuery = "DELETE FROM customers WHERE id = ?;";
		try(Connection conn = DBHelper.getConnection();
				PreparedStatement ps = conn.prepareStatement(deleteQuery)) {
			ps.setString(1, id);
			
			return ps.executeUpdate() > 0;
		}
		catch (Exception e) {
			return false;
		}
	}
}
