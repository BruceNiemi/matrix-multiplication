module matrix_multiplication(
    input [7:0] matrixA [0:3][0:3],
    input [7:0] matrixB [0:3][0:3],
    output reg [15:0]  matrixC [0:3][0:3]
);

// we need to explicitly define the for loop constants
integer i;
integer j;
integer k;

always @(*) begin
    for(i =  0; i < 4; i++)
        begin
            for(j = 0; j < 4; j++)
                begin
                    matrixC[i][j] = 0;

                    for(k = 0; k < 4; k++)
                    begin
                        matrixC[i][j] = matrixC[i][j] + (matrixA[i][k] * matrixB[k][j]);
                    end
                end
        end
end


endmodule