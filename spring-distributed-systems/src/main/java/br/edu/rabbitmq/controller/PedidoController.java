package br.edu.rabbitmq.controller;

import br.edu.rabbitmq.dto.PedidoRequest;
import br.edu.rabbitmq.model.Pedido;
import br.edu.rabbitmq.service.PedidoService;
import jakarta.validation.Valid;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.net.URI;
import java.util.List;

/**
 * A API responde imediatamente com 202 Accepted: estoque, pagamento e
 * notificação são processados de forma assíncrona pelos consumidores.
 */
@RestController
@RequestMapping("/pedidos")
public class PedidoController {

    private final PedidoService service;

    public PedidoController(PedidoService service) {
        this.service = service;
    }

    @PostMapping
    public ResponseEntity<Pedido> criar(@Valid @RequestBody PedidoRequest request) {
        Pedido pedido = service.criar(request);
        return ResponseEntity.accepted()
                .location(URI.create("/pedidos/" + pedido.id()))
                .body(pedido);
    }

    @PostMapping("/{id}/pagamento")
    public ResponseEntity<Pedido> pagar(@PathVariable Long id) {
        return ResponseEntity.accepted().body(service.pagar(id));
    }

    @PostMapping("/{id}/cancelamento")
    public ResponseEntity<Pedido> cancelar(@PathVariable Long id) {
        return ResponseEntity.accepted().body(service.cancelar(id));
    }

    @GetMapping
    public List<Pedido> listar() {
        return service.listar();
    }

    @GetMapping("/{id}")
    public Pedido buscar(@PathVariable Long id) {
        return service.buscar(id);
    }
}
