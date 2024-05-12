/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package trabalho1bd;

import com.mysql.cj.jdbc.DatabaseMetaData;
import com.mysql.cj.jdbc.result.ResultSetMetaData;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreePath;

/**
 *
 * @author gomes
 */
public class JanelaPrincipal extends javax.swing.JFrame {

    protected String login;
    protected String senha;
    protected String url;
    protected Connection con;
    private int mysql = 0;
    protected Statement stmt;
    private javax.swing.JTree jTree;
    private java.sql.DatabaseMetaData metadata;
    private String lastClicked = null;
    public JanelaPrincipal(String login, String senha, String url) {
        initComponents();
        this.setTitle("Janela Principal");
        //passagem de parametros da janela login
        this.login = login;
        this.senha = senha;
        this.url = url;
        try{
        con = DriverManager.getConnection("jdbc:"+url, login, senha);
        if (url.indexOf("mysql") == 0)
            mysql = 1;
        else
            mysql = 0;
        System.out.println(mysql);
        stmt = con.createStatement();
        this.metadata = con.getMetaData();
        updateTree();
        } catch(SQLException e)
        {
            System.out.println(e.getMessage());
        }

    }
    
    
    private void updateTree()
    {
        ResultSet rs;
        //criar root da arvore
        DefaultMutableTreeNode root = new DefaultMutableTreeNode(url);
        try{
            ResultSet rsc = null;
            if (mysql == 1)
                rs =  metadata.getCatalogs();
            else
            {
                rsc = metadata.getCatalogs();
                rs =  metadata.getSchemas();
            }
            
            while(rs.next())
            {   
                String auxName = rs.getString(1);
                DefaultMutableTreeNode auxNode = new DefaultMutableTreeNode(auxName);
                root.add(auxNode);
                DefaultMutableTreeNode tableNode = new DefaultMutableTreeNode("Tables");
                DefaultMutableTreeNode viewNode = new DefaultMutableTreeNode("views");
                auxNode.add(tableNode);
                auxNode.add(viewNode);
                ResultSet rsAux;
                if (mysql == 1)
                    rsAux = metadata.getTables(rs.getString(1), null, "%", new String[] {"TABLE"});
                else
                {
                    rsAux = stmt.executeQuery("SELECT tablename FROM pg_catalog.pg_tables WHERE schemaname != 'pg_catalog' AND schemaname != 'information_schema';");
                    
                }
                    //rsAux = metadata.getTables(rs.getString(1), null, "%", new String[] {"TABLE"});
                
                while(rsAux.next())
                {
                    String tmpName = null;
                    if (mysql == 1)
                    {
                        tmpName = rsAux.getString(3);
                    }
                    else
                        tmpName = rsAux.getString(1);
                    
                    DefaultMutableTreeNode tmpNode = new DefaultMutableTreeNode(tmpName);
                    tableNode.add(tmpNode);
                    DefaultMutableTreeNode colNode = new DefaultMutableTreeNode("Columns");
                    DefaultMutableTreeNode indNode = new DefaultMutableTreeNode("Indexes");
                    DefaultMutableTreeNode fkNode = new DefaultMutableTreeNode("Foreign Keys");
                    DefaultMutableTreeNode trigNode = new DefaultMutableTreeNode("Triggers");
                    
                    tmpNode.add(colNode);
                    tmpNode.add(indNode);
                    tmpNode.add(fkNode);
                    tmpNode.add(trigNode);
                    if (mysql == 1)
                    {
                        ResultSet rsTable = metadata.getColumns(null, null, rsAux.getString(3), null);
                        while(rsTable.next())
                        {
                            colNode.add(new DefaultMutableTreeNode(rsTable.getString(4)));
                        }
                        rsTable = metadata.getIndexInfo(null, null, rsAux.getString(3), true, false);
                        while(rsTable.next())
                        {
                            indNode.add(new DefaultMutableTreeNode(rsTable.getString(6)));
                        }
                        rsTable = metadata.getImportedKeys(null, null, rsAux.getString(3));
                        while(rsTable.next())
                        {
                            fkNode.add(new DefaultMutableTreeNode(rsTable.getString(12)));
                        }
                        rsTable = metadata.getTables(null, null, rsAux.getString(3), new String[] {"TRIGGER"});
                        while(rsTable.next())
                        {
                            fkNode.add(new DefaultMutableTreeNode(rsTable.getString(3)));
                        }
                    }
                    else
                    {
                        ResultSet rsTable = metadata.getColumns(null, null, rsAux.getString(1), null);
                        while(rsTable.next())
                        {
                            colNode.add(new DefaultMutableTreeNode(rsTable.getString(4)));
                        }
                        rsTable = metadata.getIndexInfo(null, null, rsAux.getString(1), true, false);
                        while(rsTable.next())
                        {
                            indNode.add(new DefaultMutableTreeNode(rsTable.getString(6)));
                        }
                        rsTable = metadata.getImportedKeys(null, null, rsAux.getString(1));
                        while(rsTable.next())
                        {
                            fkNode.add(new DefaultMutableTreeNode(rsTable.getString(12)));
                        }
                        rsTable = metadata.getTables(null, null, rsAux.getString(1), new String[] {"TRIGGER"});
                        while(rsTable.next())
                        {
                            fkNode.add(new DefaultMutableTreeNode(rsTable.getString(3)));
                        }
                    }
                    
                }
                rsAux = metadata.getTables(rs.getString(1), null, "%", new String[] {"VIEW"});
                while(rsAux.next())
                {
                    String tmpName = rsAux.getString(3);
                    DefaultMutableTreeNode tmpNode = new DefaultMutableTreeNode(tmpName);
                    viewNode.add(tmpNode);
                    ResultSet rsView = metadata.getColumns(null, null, rsAux.getString(3), null);
                    while(rsView.next())
                    {
                        tmpNode.add(new DefaultMutableTreeNode(rsView.getString(4)));
                    }
                }
            }
            
        } catch(SQLException e)
        {
            System.out.println(e.getMessage() + "2");
        }
        jTree = new javax.swing.JTree(root);
        jTree.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTreeMouseClicked(evt);
            }
        });
        add(jTree);
        jTree.setRootVisible(false);
        jScrollPane2.setViewportView(jTree);
        this.pack();
    }
    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jScrollPane2 = new javax.swing.JScrollPane();
        jLabel1 = new javax.swing.JLabel();
        jButton1 = new javax.swing.JButton();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jScrollPane3 = new javax.swing.JScrollPane();
        jTextArea1 = new javax.swing.JTextArea();
        jScrollPane1 = new javax.swing.JScrollPane();
        jTextArea2 = new javax.swing.JTextArea();
        jButton2 = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        jLabel1.setText("Databases");

        jButton1.setText("R");
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });

        jTextArea1.setColumns(20);
        jTextArea1.setRows(5);
        jScrollPane3.setViewportView(jTextArea1);

        jTextArea2.setColumns(20);
        jTextArea2.setRows(5);
        jScrollPane1.setViewportView(jTextArea2);

        jButton2.setText("execute");
        jButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton2ActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 157, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel1)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(jButton1, javax.swing.GroupLayout.PREFERRED_SIZE, 57, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(jScrollPane3)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jLabel2)
                            .addComponent(jLabel3)
                            .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 624, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(jButton2)))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel1)
                    .addComponent(jButton1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jScrollPane3)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jButton2)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(jLabel2)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jLabel3)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jScrollPane1))))
                    .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 458, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(14, 14, 14))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed
        updateTree();
    }//GEN-LAST:event_jButton1ActionPerformed

    private void jButton2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton2ActionPerformed
        try {
            // TODO add your handling code here:
            TreePath tp = jTree.getSelectionPath();
            String query = jTextArea2.getText();
            int select = 0;
            
            if (!query.equals(""))
            {
                if (mysql == 1)
                {
                    System.out.println("use "+ tp.getPathComponent(1).toString() +"; " + query);
                    stmt.executeQuery("use "+ tp.getPathComponent(1).toString() +";");
                }

                
                if (query.indexOf("select") == 0 || query.indexOf("SELECT") == 0)
                    select = 1;
                
                
                if (select == 1)
                {
                    if (mysql == 1)
                        stmt.executeQuery("use "+ tp.getPathComponent(1).toString() +";");
                    ResultSet rsU = stmt.executeQuery(query);
                    java.sql.ResultSetMetaData rsUmt = rsU.getMetaData();
                    String textFull="";
                    int i = 1;
                    while(i <=rsUmt.getColumnCount()){
                        textFull += rsUmt.getColumnName(i)+"\t";
                        i++;
                    }
                    textFull += "\n";
                    while(rsU.next())
                    {
                        i = 1;
                        while(i <=rsUmt.getColumnCount()){
                            textFull += rsU.getString(i)+"\t";
                            i++;
                        }
                        textFull += "\n";
                    }
                    jTextArea1.setText(textFull);
                }
                else
                {
                    if (mysql == 1)
                    {
                        System.out.println("use "+ tp.getPathComponent(1).toString() +"; " + query);
                        stmt.executeQuery("use "+ tp.getPathComponent(1).toString() +";");
                    }
                    
                    stmt.executeUpdate(query);
                }
            }
        } catch(SQLException|NullPointerException e)
        {
            System.out.println(e.getMessage());
        }
    }//GEN-LAST:event_jButton2ActionPerformed

    private void jTreeMouseClicked(java.awt.event.MouseEvent evt) {
        
        TreePath tp = jTree.getSelectionPath();
        try{
             if(tp.getPathCount()>3){
                System.out.println(tp.getPathComponent(3).toString());
                ResultSet rsTable = metadata.getColumns(null, null,tp.getPathComponent(3).toString(), null);
                if(tp.getPathComponent(3).toString().equalsIgnoreCase(lastClicked))
                    updateTableDoubleClick(tp);
                else
                    updateTable(rsTable);
                lastClicked = tp.getPathComponent(3).toString();
             }
        }
        catch(SQLException|NullPointerException e)
        {
            System.out.println(e.getMessage());
        }
    }                                   
    private void updateTable(ResultSet rsTable) throws SQLException
    {   
       String textFull = "Field\tType\tNull\n";
       while(rsTable.next())
       {    
           textFull += rsTable.getString(4)+"\t"+rsTable.getString(6)+"\t"+rsTable.getString(18)+"\n";
       }
       rsTable.last();
       jLabel3.setText(rsTable.getString(3));
       jTextArea1.setText(textFull);

    }
    
    private void updateTableDoubleClick(TreePath tp) throws SQLException
    {
        if (mysql == 1)
        {
            System.out.println("use "+ tp.getPathComponent(1).toString() +"; select * from "+tp.getPathComponent(3).toString() + " limit 20;");
             stmt.executeQuery("use "+ tp.getPathComponent(1).toString() +";");
        }
        ResultSet rsU = stmt.executeQuery("select * from "+tp.getPathComponent(3).toString()+" limit 20;");
        java.sql.ResultSetMetaData rsUmt = rsU.getMetaData();
        String textFull="";
            int i = 1;
            while(i <=rsUmt.getColumnCount()){
                textFull += rsUmt.getColumnName(i)+"\t";
                i++;
            }
        textFull += "\n";
        while(rsU.next())
        {
            i = 1;
            while(i <=rsUmt.getColumnCount()){
                textFull += rsU.getString(i)+"\t";
                i++;
            }
            textFull += "\n";
        }
        jTextArea1.setText(textFull);
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(JanelaPrincipal.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(JanelaPrincipal.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(JanelaPrincipal.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(JanelaPrincipal.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new JanelaLogin().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jButton1;
    private javax.swing.JButton jButton2;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JScrollPane jScrollPane3;
    private javax.swing.JTextArea jTextArea1;
    private javax.swing.JTextArea jTextArea2;
    // End of variables declaration//GEN-END:variables
}
