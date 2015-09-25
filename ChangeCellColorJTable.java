
import java.awt.Color;
import java.awt.Component;
import javax.swing.JOptionPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;

public class ChangeCellColorJTable extends javax.swing.JFrame {

    public static Color[][] table_color = new Color[40][40];
    public static Object[][] table_value = new Object[40][40];
    
    public ChangeCellColorJTable() {
        initComponents();
        initTable();
        refreshtable(mytable,1,1);
    }

    public static void initTable(){
        int i,j;
        Object[][] data = new Object[][]{
                {10,10},
                {11,11},
                {12,12},
                {13,13}
        };
        for(i = 0;i < 4;i++ ){
            for(j = 0;j<2;j++){
                mytable.setValueAt(data[i][j], i, j);
                table_value[i][j] = data[i][j];
            }
        }
        for(i = 0;i<4;i++){
            for(j = 0;j<2;j++){
                table_color[i][j] = Color.getColor("#f9f4bd");
                table_color[i][j] = Color.getColor("#ffffff");
            }
        }
    }
    private void initComponents() {
        jScrollPane1 = new javax.swing.JScrollPane();
        mytable = new javax.swing.JTable();
        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        mytable.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null},
                {null, null},
                {null, null},
                {null, null}
            },
            new String [] {
                "Title 1", "Title 2"
            }
        ));
        mytable.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                mytableMouseClicked(evt);
            }
        });
        jScrollPane1.setViewportView(mytable);
        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 375, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(13, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(13, Short.MAX_VALUE)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 275, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
       pack();
    }
    private void mytableMouseClicked(java.awt.event.MouseEvent evt) {           //MouseClickEvent                             
        int row,column;
        Color colr = Color.CYAN;
        JTable target = (JTable)evt.getSource();
        row = target.getSelectedRow();
        column = target.getSelectedColumn();
        //JOptionPane.showMessageDialog(null, "row "+row+" column "+column);
        setColorAtCell(mytable,colr,row,column);        //Set Color At Cell Function >> Written By Rakesh Gunduka 
    }           

    public static void refreshtable(JTable table,int row,int column){
        int i;
        try{
            mytable.getColumnModel().getColumn(column).setCellRenderer(new Custom_Renderer());
        }catch(Exception e){
            JOptionPane.showMessageDialog(null, "error there");
        }
    }
    public static void setColorAtCell(JTable table,Color colr,int row,int column){
        table_color[row][column] = colr;
        refreshtable(table,row,column);
        refreshtable(table,row,column);
    }
    
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new ChangeCellColorJTable().setVisible(true);
            }
        });
    }

    private javax.swing.JScrollPane jScrollPane1;
    public static javax.swing.JTable mytable;               
}


class Custom_Renderer extends DefaultTableCellRenderer 
{
    Custom_Renderer(){
        
    }
        
    @Override
    public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column)
    {
        Component cellComponent = super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
        Object value_present = table.getValueAt(row, column);
        Object value_in_table = ChangeCellColorJTable.table_value[row][column];
        if(value_present.equals(value_in_table)){
            Color color = ChangeCellColorJTable.table_color[row][column];
            cellComponent.setBackground(color);
        }else{
            cellComponent.setBackground(Color.blue);
        }
        return cellComponent;
    }
}
