package br.edu.rabbitmq.dto;

import jakarta.validation.constraints.NotBlank;

/** Corpo da Etapa 2: { "mensagem": "Olá RabbitMQ" } */
public record MensagemRequest(
        @NotBlank(message = "mensagem é obrigatória") String mensagem
) {
}
