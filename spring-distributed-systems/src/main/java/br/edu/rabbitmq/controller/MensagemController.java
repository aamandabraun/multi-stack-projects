package br.edu.rabbitmq.controller;

import br.edu.rabbitmq.dto.MensagemRequest;
import br.edu.rabbitmq.producer.MensagemProducer;
import jakarta.validation.Valid;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

/** Etapa 2: POST /mensagens → Controller → Producer → RabbitMQ → Queue → Consumer */
@RestController
@RequestMapping("/mensagens")
public class MensagemController {

    private final MensagemProducer producer;

    public MensagemController(MensagemProducer producer) {
        this.producer = producer;
    }

    @PostMapping
    public ResponseEntity<Map<String, String>> enviar(@Valid @RequestBody MensagemRequest request) {
        producer.enviar(request);
        return ResponseEntity.accepted().body(Map.of("status", "Mensagem enviada para processamento"));
    }
}
