package ciarem.dao;

import java.sql.*;

public class DBHelper {
	private static final String url = "jdbc:sqlite:ciarem.db";
	
	public static void init() {
		try(Connection conn = DriverManager.getConnection(url);
				Statement s = conn.createStatement()){
			String initQuery = "CREATE TABLE IF NOT EXISTS customers("
				+ "id INTEGER PRIMARY KEY,"
				+ "NAME TEXT NOT NULL,"
				+ "PHONE TEXT,"
				+ "DOB INTEGER"
				+ ");";
			s.execute(initQuery);
			System.out.print("DB init success");
				
		}
		catch(Exception e) {
			System.out.print("DB init failed: " + e.getMessage());
		}
	}
	
	public static Connection getConnection() throws Exception {
		return DriverManager.getConnection(url);
	}
}
