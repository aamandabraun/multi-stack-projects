package br.edu.rabbitmq.dto;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Positive;

import java.math.BigDecimal;

public record PedidoRequest(
        @NotBlank(message = "cliente é obrigatório") String cliente,
        @NotBlank(message = "produto é obrigatório") String produto,
        @NotNull(message = "quantidade é obrigatória") @Positive(message = "quantidade deve ser maior que zero") Integer quantidade,
        @NotNull(message = "valor é obrigatório") @Positive(message = "valor deve ser maior que zero") BigDecimal valor
) {
}
