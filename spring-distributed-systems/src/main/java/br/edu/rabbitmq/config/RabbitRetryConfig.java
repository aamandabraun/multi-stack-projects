package br.edu.rabbitmq.config;

import org.springframework.amqp.AmqpRejectAndDontRequeueException;
import org.springframework.amqp.support.converter.MessageConversionException;
import org.springframework.boot.autoconfigure.amqp.RabbitProperties;
import org.springframework.boot.autoconfigure.amqp.RabbitRetryTemplateCustomizer;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.retry.policy.SimpleRetryPolicy;

import java.util.Map;

/**
 * Retry só faz sentido para falhas transitórias. Mensagem inválida continua
 * inválida na 2ª tentativa, então vai direto para a DLQ.
 */
@Configuration
public class RabbitRetryConfig {

    @Bean
    public RabbitRetryTemplateCustomizer naoRetentarMensagensInvalidas(RabbitProperties properties) {
        int maxTentativas = properties.getListener().getSimple().getRetry().getMaxAttempts();

        return (target, template) -> {
            if (target == RabbitRetryTemplateCustomizer.Target.LISTENER) {
                template.setRetryPolicy(new SimpleRetryPolicy(
                        maxTentativas,
                        Map.of(
                                AmqpRejectAndDontRequeueException.class, false,
                                MessageConversionException.class, false
                        ),
                        true, // procura a causa dentro de ListenerExecutionFailedException
                        true  // demais exceções: retentar
                ));
            }
        };
    }
}
